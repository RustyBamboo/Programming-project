#include "HandshakeResponse.hpp"
sf::Packet& operator <<(sf::Packet& packet, const HandshakeResponse& x)
{
    return packet << x.id;
}

sf::Packet& operator >>(sf::Packet& packet, HandshakeResponse& x)
{
    return packet >> x.id;
}
