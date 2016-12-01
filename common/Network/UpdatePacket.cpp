#include "UpdatePacket.hpp"
UpdatePacket::UpdatePacket(uint8_t u_type, uint32_t u_id) :
  type(u_type),
  id(u_id)
{}
UpdatePacket::UpdatePacket(){}
sf::Packet& operator <<(sf::Packet& packet, const UpdatePacket& x)
{
    return packet << x.type << x.id;
}

sf::Packet& operator >>(sf::Packet& packet, UpdatePacket& x)
{
    return packet >> x.type >> x.id;
}
