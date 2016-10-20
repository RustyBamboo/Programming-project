#include "UpdatePacket.hpp"
sf::Packet& operator <<(sf::Packet& packet, const UpdatePacket& x)
{
    return packet << x.type << x.id;
}

sf::Packet& operator >>(sf::Packet& packet, UpdatePacket& x)
{
    return packet >> x.type >> x.id;
}
