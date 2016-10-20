#pragma once
#include <SFML/Network.hpp>
struct TickPacket
{
	uint32_t tick_number;
	uint32_t num_updates;
};
sf::Packet& operator <<(sf::Packet& packet, const TickPacket& x);
sf::Packet& operator >>(sf::Packet& packet, TickPacket& x);
