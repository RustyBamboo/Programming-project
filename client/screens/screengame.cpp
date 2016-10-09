#include "screengame.hpp"

ScreenGame::ScreenGame()
{
	
}
void ScreenGame::doTick()
{
	sf::Packet packet;
	TickPacket tp;
	packet >> tp;
	if (tp.tick_number != last_packet + 1)
	{
		std::cout << "Wrong packet num" << std::endl;
		return;
	}
	for (uint i = 0; i < tp.num_updates; i++)
	{
		UpdatePacket update;
		packet >> update;
		switch (update.type)
		{
			case 1:
				{
					worldMap.removeEntity(update.id);
				}
				break;
			case 2:
				{
					Entity* e = worldMap.getEntity(update.id);
					*e << packet;
				}
				break;
			case 3:
				{
					Polygon* p = (Polygon*) worldMap.getEntity(update.id);
					*p << packet;
				}
				break;
			case 4:
				{
					Polygon *p = new Polygon();
					*p << packet;
					worldMap.addEntity(update.id,p);
				}
				break;
		}
			//Do update depending on type
	}
}
void ScreenGame::doHandshake()
{
	sf::TcpSocket tcp_socket;
	if (tcp_socket.connect(IP_ADDRESS, TCP_PORT) == sf::Socket::Done) {
		HandshakeRequest req;
		sf::Packet req_packet;
		req_packet << req;
		tcp_socket.send(req_packet);
		sf::Packet res_packet;
		tcp_socket.receive(res_packet);
		HandshakeResponse res;
		res_packet >> res;
	}	
}


int ScreenGame::run(sf::RenderWindow &window) 
{
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
		else doTick();
	}
}
