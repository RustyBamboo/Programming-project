#include "entity.hpp"

Entity::Entity() {
    std::cout << "Generated Default Entity" << std::endl;
    x = rand()%500;
    y = rand()%500;
    id = rand()%100;
}

Entity::Entity(std::string user) {
    std::cout << "Generated entity" << user << std::endl;
}
