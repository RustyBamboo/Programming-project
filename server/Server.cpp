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
	tickPacket.tick_number = 0;
	tickPacket.num_updates = 0;
	tick_number = 0;
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
		updates_packet.clear();
	}
	sf::Clock clock;
	clock.restart();
	while (clock.getElapsedTime().asMilliseconds() < TICK_TIME_MILLIS)
	{
		for(std::map< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end(); player++)
		{
			(*player).first->setBlocking(false);
			UpdatePacket update;
			sf::Packet packet;
			sf::Socket::Status status = (*player).first->receive(packet);
			if (status == sf::Socket::Status::Done)
			{
				packet >> update;
				printf("Received Update TYPE=%u ID=%u\n",update.type,update.id);
				switch (update.type)
				{
					case UpdatePacket::UPDATE_ENTITY:
						{
							Entity* e = worldMap.getEntity(update.id);
							*e << packet;
							{
								sf::Lock lock(tick_mutex);
								updates_packet << update;
								*e >> updates_packet;
								tickPacket.num_updates++;
							}
						}
						break;
				}	
			}			
		}
		sf::sleep(sf::milliseconds(10));
	}
	
	//Ready to send tick
	sf::Lock lock(tick_mutex);
	sf::Packet header_packet;
	header_packet << tickPacket;
	printf("Sending Tick #%u Updates=%i Players=%i SIZE=%u\n",tickPacket.tick_number,tickPacket.num_updates,players.size(),updates_packet.getDataSize ());
	for(std::map< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end(); player++)
	{
		(*player).first->setBlocking(true);
		(*player).first->send(header_packet);
		(*player).first->send(updates_packet);	
	}
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
			std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);

			newPlayersListener.accept(*client);
			client->receive(req_packet);
			req_packet >> req;
			//Create new player entity
			Polygon* character = new Polygon();
			auto id = worldMap.newEntity((Entity*) character);
			
			//Send player response with their character id
			res.id = id;
			res_packet << res;
			client->send(res_packet);
			{
				sf::Lock lock(tick_mutex);
				UpdatePacket update;
				update.type = UpdatePacket::NEW_POLYGON;
				update.id = id;
				updates_packet << update;
				*character >> updates_packet;
				tickPacket.num_updates++;
			}
			std::cout << "Added IP: " << client->getRemoteAddress() << std::endl;
			players.insert(std::pair< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE>(std::move(client),id) );
	}
}
