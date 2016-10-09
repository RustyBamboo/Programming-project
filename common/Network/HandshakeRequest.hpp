#ifndef fsdfssd
#define fsdfssd
#include <SFML/Network.hpp>
struct HandshakeRequest
{
	std::string name;
};
sf::Packet& operator <<(sf::Packet& packet, const HandshakeRequest& x);
sf::Packet& operator >>(sf::Packet& packet, HandshakeRequest& x);

#endif
