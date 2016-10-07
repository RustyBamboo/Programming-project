//THIS IS FOR TESTING
#ifndef MOB_HPP
#define MOB_HPP

#include "entity.hpp"
#include "polygon.hpp"
class Mob : public Entity {
public:
    Mob(sf::Vector2f p, sf::Vector2f v);
    Mob(int size, int edges, sf::Vector2f p, sf::Vector2f v);
    virtual void move();
};

#endif