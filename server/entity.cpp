#include "entity.hpp"

Entity::Entity() {
    std::cout<<"Generated Default Entity"<<std::endl;
    x = 0;
    y = 50;
}

Entity::Entity(std::string user) {
    std::cout<<"Generated entity"<<user<<std::endl;
}
