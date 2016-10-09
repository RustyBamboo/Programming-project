#include "screengame.hpp"
#include <string>
ScreenGame::ScreenGame() :
	SERVER_IP(sf::IpAddress::LocalHost)
{
	
}
void ScreenGame::doTick()
{
	std::cout << "Do Tick" << std::endl;
	sf::IpAddress remoteAddress;
	unsigned short remotePort;
	sf::Packet packet;
	TickPacket tp;
	udpSocket.receive(packet,remoteAddress,remotePort);
	if (remoteAddress != SERVER_IP)
	{
		std::cout << "Received from not server, ignoring" << std::endl;
		return;
	}
	packet >> tp;
	//~ if (tp.tick_number != last_packet + 1)
	//~ {
		//~ std::cout << "Wrong packet num" << std::endl;
		//~ return;
	//~ }
	for (uint i = 0; i < tp.num_updates; i++)
	{
		UpdatePacket update;
		sf::Packet packet;
		do {
			packet.clear();
			udpSocket.receive(packet,remoteAddress,remotePort);
		} while (remoteAddress != SERVER_IP);
		packet >> update;
		switch (update.type)
		{
			case UpdatePacket::REMOVE_ENTITY:
				{
					worldMap.removeEntity(update.id);
				}
				break;
			case UpdatePacket::UPDATE_ENTITY:
				{
					Entity* e = worldMap.getEntity(update.id);
					*e << packet;
				}
				break;
			case UpdatePacket::UPDATE_POLYGON:
				{
					Polygon* p = (Polygon*) worldMap.getEntity(update.id);
					*p << packet;
				}
				break;
			case UpdatePacket::NEW_POLYGON:
				{
					Polygon *p = new Polygon();
					*p << packet;
					worldMap.addEntity(update.id,p);
				}
				break;
		}
			//Do update depending on type
	}
	worldMap.tick();
}
void ScreenGame::doHandshake()
{
	sf::TcpSocket tcp_socket;
	if (tcp_socket.connect(SERVER_IP, TCP_PORT) == sf::Socket::Done) {
		HandshakeRequest req;
		sf::Packet req_packet;
		req_packet << req;
		tcp_socket.send(req_packet);
		sf::Packet res_packet;
		tcp_socket.receive(res_packet);
		HandshakeResponse res;
		res_packet >> res;
	}	
	std::cout << "Did Handshake" << std::endl;
}
void ScreenGame::handleUserInput()
{
	Entity* me = worldMap.getEntity(player_id);
	sf::Vector2f velocity = me->getVelocity();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y = -1;
	} else {
		velocity.x = 0;
		velocity.y = 0;
	}
	
	if (velocity != me->getVelocity())
	{
		sf::Packet packet;
		UpdatePacket update;
		update.id = player_id;
		update.type = UpdatePacket::UPDATE_ENTITY;
		packet << update;
		*me >> packet;
	}
}
int ScreenGame::run(sf::RenderWindow &window) 
{
	std::cout << "Game Running" << std::endl;
	doHandshake();
	sf::Event Event;
	udpSocket.bind(UDP_PORT);
	while (window.pollEvent(Event)) {
		if (Event.type == sf::Event::Closed) {
			return (-1);
		}
		else if (Event.type == sf::Event::KeyPressed) {
			switch (Event.key.code) {
				case sf::Keyboard::Escape:
					return (0); //Goes to Pause Menu
			}
		}
		else {
			doTick();
			worldMap.draw(window);
		}
	}
}
