#ifndef WORLDMAP_SERVER_HPP
#define WORLDMAP_SERVER_HPP
#include <map>
#include "entity.hpp"
#include <SFML/Network.hpp>
#include "player.hpp"

class WorldMap {
private:
    const unsigned short UDPSENDTOPORT = 5003; //Udp port open for client
    std::map<int, Entity> entities;
    std::vector<sf::IpAddress> ipAddresses;
public:
    WorldMap();
    void genEntity(int id);
    void genEntity(int id, std::string name, sf::IpAddress address);
    void update(sf::UdpSocket &udpSocket); //Sends out to all clients
    void update(int id, int x, int y); //Moves entities
};

#endif