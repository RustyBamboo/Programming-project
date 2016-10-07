#include "worldmap.hpp"

WorldMap::WorldMap() {

}

void WorldMap::genEntity(std::string name) {
    entities[name] = Entity("haha");
}
void WorldMap::genEntity(std::string name, sf::IpAddress address) {
    entities[name] = Player();
    ipAddresses.push_back(address);
}

void WorldMap::update(sf::UdpSocket &udpSocket) {
    std::cout<<"connected ipAddresses: "<<std::endl;
    for(const sf::IpAddress &a : ipAddresses) {
        std::cout<<"\t"<<a<<std::endl;
        std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
        udpSocket.send(message.c_str(), message.size() + 1, a, 55002);
    }
}