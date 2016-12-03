#pragma once
#include <map>
#include "../include.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

class WorldMap {
public:
    typedef uint32_t ID_TYPE;
    typedef std::map<ID_TYPE, std::unique_ptr<Entity> > entities_t;
    typedef entities_t::iterator it_type;

    WorldMap();

    void tick();
    int checkCollisions(sf::Packet &packet);
    int checkOutOfMap(sf::Packet &packet);
    void draw(sf::RenderWindow &window);

    static double ZOOM_FACTOR;
    static int width;
    static int height;

    bool isOutOfMap(sf::FloatRect rect);

    void addEntity(ID_TYPE id, Entity* e); //Add an enttiy with given ID, returning a NULL pointer to
    Entity* getEntity(ID_TYPE id); //Returns a pointer to an entity in the map with given ID, use for updating
    void removeEntity(ID_TYPE id); //Erases a pointer
    ID_TYPE newEntity(Entity* e);
    entities_t entities;
private:
    ID_TYPE last_id;
};
