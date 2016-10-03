#include "entity.h"
 
Entity::Entity() {

}

void Entity::tick() {
	move();
	pos+=vel;
	obj->setPosition(pos);
}

void Entity::draw(sf::RenderWindow &window) {
	obj->draw(window);
}