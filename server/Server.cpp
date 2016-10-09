#include "Server.hpp"
Server::Server()
{
	
}
void Server::run()
{	
	if (newPlayersListener.listen(TCP_PORT) == sf::TcpListener::Error) {
			newPlayersListener.close();
			newPlayersListener.listen(TCP_PORT);
	}
	tickSocket.bind(UDP_PORT);
	tickSocket.setBlocking(false);
	sf::Thread newPlayersThread(&Server::connectPlayers,this);
	newPlayersThread.launch();
	while (true) tick();
}
void Server::tick()
{
	std::cout << "Server Tick" << std::endl;
	{
		sf::Lock lock(tick_mutex);
		tickPacket.tick_number = tick_number;
		tickPacket.num_updates = 0;
		updates_packet = sf::Packet();
	}
	sf::Clock clock;
	clock.restart();
	while (clock.getElapsedTime().asMilliseconds() < TICK_TIME_MILLIS)
	{
		sf::Packet update_packet;
		sf::IpAddress remoteAddress;
		unsigned short remotePort;
		sf::Socket::Status status = tickSocket.receive(update_packet,remoteAddress,remotePort);
		if (status == sf::Socket::Status::Done)
		{
			UpdatePacket update;
			update_packet >> update;
			switch (update.type)
			{
				case UpdatePacket::UPDATE_ENTITY:
					{
						Entity* e = worldMap.getEntity(update.id);
						*e << update_packet;
						{
							sf::Lock lock(tick_mutex);
							updates_packet << update;
							*e >> updates_packet;
							tickPacket.num_updates++;
						}
					}
					break;
			}	
		} else sf::sleep(sf::milliseconds(10));
	}
	
	//Ready to send tick
	sf::Lock lock(tick_mutex);
	sf::Packet header_packet;
	header_packet << tickPacket;
	printf("Sending Updates. Players=%i Updates=%i\n",players.size(),tickPacket.num_updates);
	std::for_each(players.begin(),players.end(),[&] (std::pair<sf::IpAddress,WorldMap::ID_TYPE> player) {
		const sf::IpAddress remoteAddress = player.first;
		tickSocket.send(header_packet,remoteAddress,UDP_PORT);
		tickSocket.send(updates_packet,remoteAddress,UDP_PORT);
	});
	worldMap.tick();
	tick_number++;
}
void Server::connectPlayers()
{
	while (true) 
	{
			HandshakeRequest req;
			HandshakeResponse res;
			sf::Packet req_packet,res_packet;
			sf::TcpSocket client;
			
			
			newPlayersListener.accept(client);
			client.receive(req_packet);
			req_packet >> req;
			//Create new player entity
			Entity* character = (Entity*) new Polygon();
			auto id = worldMap.newEntity(character);
			
			//Send player response with their character id
			res.id = id;
			res_packet << res;
			client.send(res_packet);
			
			players.insert(std::pair<sf::IpAddress,WorldMap::ID_TYPE>(client.getRemoteAddress(),id)); //Add ip to players list
			{
				sf::Lock lock(tick_mutex);
				UpdatePacket update;
				update.type = UpdatePacket::NEW_POLYGON;
				update.id = id;
				updates_packet << update;
				*character >> updates_packet;
				tickPacket.num_updates++;
			}
			std::cout << "Added IP: " << client.getRemoteAddress() << std::endl;
	}
}
