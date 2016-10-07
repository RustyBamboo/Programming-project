#include "entity.hpp"

Entity::Entity(){
    std::cout<<"hmm"<<std::endl;
}

Entity::Entity(std::string user) : name(user) {
    std::cout << "Generated entity" << user << std::endl;
}
