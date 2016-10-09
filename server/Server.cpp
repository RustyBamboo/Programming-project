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
	sf::Clock clock;
	while (clock.getElapsedTime().asMilliseconds() < TICK_TIME_MILLIS)
	{
		sf::Packet update_packet;
		sf::IpAddress remoteAddress;
		unsigned short remotePort;
		sf::Socket::Status status = tickSocket.receive(update_packet,remoteAddress,remotePort);
		if (status == sf::Socket::Status::Done)
		{
			//Process packet
		} else sf::sleep(sf::milliseconds(10));
		clock.restart();
	}
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
			//Create new player
			
			res_packet << res;
			client.send(res_packet);
	}
}
