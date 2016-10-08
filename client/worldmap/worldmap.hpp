/*

    This will be the main Map class that processes all the entities and updates everything.

*/

#ifndef WORLD_MAP_HPP
#define WORLD_MAP_HPP
#include <SFML/Network.hpp>
#include "../include.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/bullet.hpp"
#include "../entities/mob.hpp"
#include <memory>
#include <map>

//Testing.
class WorldMap {

private:
    int playerID;
    std::map<int, std::unique_ptr<Entity> > entities;

public:
    WorldMap();
    void addPlayer(int id);
    void tick();
    void draw(sf::RenderWindow &window);

    bool idExists(int id);

    void processEntity(int id, int x, int y);

    void sendInfo(sf::UdpSocket &udpSocket);

};

#endif