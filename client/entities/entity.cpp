#include "entity.hpp"
 
Entity::Entity() {

}

//Updates the entity, processes the Move function, adds velocity, and updates the Object
void Entity::tick() {
	move();
	pos+=vel;
	obj->setPosition(pos);
}

void Entity::draw(sf::RenderWindow &window) {
	obj->draw(window);
}