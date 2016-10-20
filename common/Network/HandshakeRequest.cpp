#include "HandshakeRequest.hpp"
sf::Packet& operator <<(sf::Packet& packet, const HandshakeRequest& x)
{
    return packet << x.name;
}

sf::Packet& operator >>(sf::Packet& packet, HandshakeRequest& x)
{
    return packet >> x.name;
}
