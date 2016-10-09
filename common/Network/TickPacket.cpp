#include "TickPacket.hpp"
sf::Packet& operator <<(sf::Packet& packet, const TickPacket& x)
{
    return packet << x.tick_number << x.num_updates;
}

sf::Packet& operator >>(sf::Packet& packet, TickPacket& x)
{
    return packet >> x.tick_number >> x.num_updates;
}
