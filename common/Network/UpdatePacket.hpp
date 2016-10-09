#pragma once
#include <SFML/Network.hpp>
struct UpdatePacket
{
	uint8_t  type;
	uint32_t id;
	
	static const uint8_t REMOVE_ENTITY=1;
	static const uint8_t UPDATE_ENTITY=2;
	static const uint8_t UPDATE_POLYGON=3;
	static const uint8_t NEW_POLYGON=4;
};
sf::Packet& operator <<(sf::Packet& packet, const UpdatePacket& x);
sf::Packet& operator >>(sf::Packet& packet, UpdatePacket& x);
