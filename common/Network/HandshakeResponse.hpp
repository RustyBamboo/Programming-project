#pragma once
#include <SFML/Network.hpp>
struct HandshakeResponse
{
	uint32_t id;
	
};
sf::Packet& operator <<(sf::Packet& packet, const HandshakeResponse& x);
sf::Packet& operator >>(sf::Packet& packet, HandshakeResponse& x);
