#ifndef WORLDMAP_SERVER_HPP
#define WORLDMAP_SERVER_HPP
#include <map>
#include "entity.hpp"
#include <SFML/Network.hpp>
#include "player.hpp"

class WorldMap {
private:
	std::map<std::string, Entity> entities;
    std::vector<sf::IpAddress> ipAddresses;
public:
    WorldMap();
    void genEntity(std::string name);
    void genEntity(std::string name, sf::IpAddress address);
    void update(sf::UdpSocket &udpSocket);

};

#endif