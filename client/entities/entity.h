#ifndef ENTITY_H
#define ENTITY_H
#include "object.hpp"
#include "../include.h"
class Entity {
protected:
	Object *obj;
	virtual void move() = 0;

public:
	Entity();

	void tick(); //We need tick functions to be synced (get diff in time)
	void draw(sf::RenderWindow &window);

	sf::Vector2f pos, vel;


};


#endif