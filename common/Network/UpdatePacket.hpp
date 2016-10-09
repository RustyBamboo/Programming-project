#pragma once
#include <SFML/Network.hpp>
struct UpdatePacket
{
	uint8_t  type;
	uint32_t id;
};
sf::Packet& operator <<(sf::Packet& packet, const UpdatePacket& x);
sf::Packet& operator >>(sf::Packet& packet, UpdatePacket& x);
