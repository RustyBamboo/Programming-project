#include "screengame.hpp"
#include <string>
ScreenGame::ScreenGame() :
	SERVER_IP(sf::IpAddress::LocalHost)
{
		std::cout << "Game Running" << std::endl;
		doHandshake();
}
void ScreenGame::doTick()
{
	sf::Packet packet;
	packet.clear();
	TickPacket tp;
	serverConnection.receive(packet);
	packet >> tp;
	//~ if (tp.tick_number != last_packet + 1)
	//~ {
		//~ std::cout << "Wrong packet num" << std::endl;
		//~ return;
	//~ }
	printf("Tick #%u updates=%u\n",tp.tick_number,tp.num_updates);
	for (uint i = 0; i < tp.num_updates; i++)
	{
		UpdatePacket update;
		sf::Packet packet;
		packet.clear();
		serverConnection.receive(packet);
		packet >> update;
		switch (update.type)
		{
			case UpdatePacket::REMOVE_ENTITY:
				{
					printf("Update REMOVE_ENTITY #%u ID=%u\n",i,update.id);
					worldMap.removeEntity(update.id);
				}
				break;
			case UpdatePacket::UPDATE_ENTITY:
				{
					printf("Update UPDATE_ENTITY #%u ID=%u\n",i,update.id);
					Entity* e = worldMap.getEntity(update.id);
					*e << packet;
				}
				break;
			case UpdatePacket::UPDATE_POLYGON:
				{
					printf("Update UPDATE_POLYGON #%u ID=%u\n",i,update.id);
					Polygon* p = (Polygon*) worldMap.getEntity(update.id);
					*p << packet;
				}
				break;
			case UpdatePacket::NEW_POLYGON:
				{
					printf("Update NEW_POLYGON #%u ID=%u\n",i,update.id);
					Polygon *p = new Polygon();
					*p << packet;
					worldMap.addEntity(update.id,p);
				}
				break;
			default:
				printf("Update UNKOWN #%u ID=%i\n",i,update.id);
		}
			//Do update depending on type
	}
	worldMap.tick();
}
void ScreenGame::doHandshake()
{
	if (serverConnection.connect(SERVER_IP, TCP_PORT) == sf::Socket::Done) {
		HandshakeRequest req;
		sf::Packet req_packet;
		req_packet << req;
		serverConnection.send(req_packet);
		sf::Packet res_packet;
		serverConnection.receive(res_packet);
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
		printf("Seting Velocity ID=%u ",player_id);
		sf::Packet packet;
		UpdatePacket update;
		update.id = player_id;
		update.type = UpdatePacket::UPDATE_ENTITY;
		packet << update;
		*me >> packet;
		serverConnection.send(packet);
	}
}
int ScreenGame::run(sf::RenderWindow &window) 
{

	sf::Event Event;
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
