#ifndef ENTITY_SERVER_HPP
#define ENTITY_SERVER_HPP
#include <iostream>
class Entity {
public:
    int x, y;
    std::string name;
    Entity();
    Entity(std::string user);

};

#endif