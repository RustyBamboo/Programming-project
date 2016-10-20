#include "Server.hpp"
Server::Server()
{
	
}
void Server::run()
{
	if (newPlayersListener.listen(TCP_PORT) == sf::TcpListener::Error)
  {
			newPlayersListener.close();
			newPlayersListener.listen(TCP_PORT);
	}
  newPlayersListener.setBlocking(false);
	tickPacket.tick_number = 0;
	tickPacket.num_updates = 0;
	tick_number = 0;
	while (true) {
    tickPacket.tick_number = tick_number;
    tickPacket.num_updates = 0;
    updates_packet.clear();
    connectPlayer();
    tick();
  }
}
void Server::tick()
{
	std::cout << "Server Tick" << std::endl;

	sf::Clock clock;
	clock.restart();
	while (clock.getElapsedTime().asMilliseconds() < TICK_TIME_MILLIS)
	{
		for(std::map< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end(); player++)
		{
			(*player).first->setBlocking(false);
			sf::Packet packet;
      sf::Socket::Status status = (*player).first->receive(packet);
      while (status == sf::Socket::Status::Done)
      {
        UpdatePacket update;
				packet >> update;
				printf("Received Update TYPE=%u ID=%u\n From",update.type,update.id);
				switch (update.type)
				{
					case UpdatePacket::UPDATE_ENTITY:
						{
							Entity* e = worldMap.getEntity(update.id);
							*e << packet;
              updates_packet << update;
              *e >> updates_packet;
              tickPacket.num_updates++;
						}
						break;
				}
        packet.clear();
        status = (*player).first->receive(packet);
      }
      if (status ==  sf::Socket::Status::Disconnected)
      {
        //Remove TCP connection,etc
      } else if (status == sf::Socket::Status::Error)
      {
        //Handle error
      }
		}
		sf::sleep(sf::milliseconds(10));
	}
	
	//Ready to send tick
	sf::Packet header_packet;
	header_packet << tickPacket;
	printf("Sending Tick #%u Updates=%i Players=%u HEADER_SIZE=%u UPDATES_SIZE=%u\n",tickPacket.tick_number,tickPacket.num_updates,players.size(),header_packet.getDataSize(),updates_packet.getDataSize ());
	for(std::map< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE>::iterator player = players.begin(); player != players.end(); player++)
	{
    printf("ONLY ONCE\n");
		(*player).first->setBlocking(true);
		(*player).first->send(header_packet);
		if(tickPacket.num_updates > 0) (*player).first->send(updates_packet);	
	}
	worldMap.tick();
	tick_number++;
}
void Server::connectPlayer()
{
    HandshakeRequest req;
    HandshakeResponse res;
    sf::Packet req_packet,res_packet;
    std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
    sf::Socket::Status  s = newPlayersListener.accept(*client);
    if (s != sf::Socket::Status::Done) return;
    client->setBlocking(true);
    client->receive(req_packet);
    printf("Recieving Handshake Request Size = %u\n",req_packet.getDataSize ());
    req_packet >> req;
    //Create new player entity
    Polygon* character = new Polygon();
    auto id = worldMap.newEntity((Entity*) character);
    //Send player response with their character id
    res.id = id;
    res_packet << res;
    printf("Sending Handshake Response Size = %u\n",res_packet.getDataSize ());
    client->send(res_packet);
    UpdatePacket update;
    update.type = UpdatePacket::NEW_POLYGON;
    update.id = id;
    updates_packet << update;
    *character >> updates_packet;
    tickPacket.num_updates++;
    std::cout << "Added IP: " << client->getRemoteAddress() << std::endl;
    players.insert(std::pair< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE>(std::move(client),id) );
}
