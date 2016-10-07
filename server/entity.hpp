#ifndef ENTITY_SERVER_HPP
#define ENTITY_SERVER_HPP
#include <iostream>
class Entity {
public:
    int id;
    int x, y;
    Entity();
    Entity(std::string user);

};

#endif