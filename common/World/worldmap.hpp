#pragma once
#include <map>
#include "../Entities/entity.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

class WorldMap {
public:
    typedef uint32_t ID_TYPE;
    WorldMap();

    void tick();
    void checkCollisions();
    void draw(sf::RenderWindow &window);

    void addEntity(ID_TYPE id, Entity* e); //Add an enttiy with given ID, returning a NULL pointer to
    Entity* getEntity(ID_TYPE id); //Returns a pointer to an entity in the map with given ID, use for updating
    void removeEntity(ID_TYPE id); //Erases a pointer
    ID_TYPE newEntity(Entity* e);
private:
    ID_TYPE last_id;
    std::map<ID_TYPE, std::unique_ptr<Entity> > entities;
};
