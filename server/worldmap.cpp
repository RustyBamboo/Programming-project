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
    std::cout << "connected ipAddresses: " << std::endl;
    for (const sf::IpAddress &a : ipAddresses) {
        std::cout << "\t" << a << std::endl;
        for (auto const &ent1 : entities) {
            std::string result;
            std::string name(12, ' ');
            std::string id(6, ' ');
            std::string xpos(9, ' ');
            std::string ypos(9, ' ');
            name.replace(0, ent1.first.size(), ent1.first);
            id.replace(0, 3, std::to_string(ent1.second.id));
            std::string X(std::to_string(ent1.second.x));
            std::string Y(std::to_string(ent1.second.y));
            xpos.replace(0, X.size(), X);
            ypos.replace(0, Y.size(), Y);

            result = name + id + xpos + ypos;
            std::cout<<result.size()<<std::endl;
            udpSocket.send(result.c_str(), result.size() + 1, a, 55002);

        }
    }
}