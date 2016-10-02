#ifndef ENTITY_H
#define ENTITY_H
#include "shape.h"
#include "../include.h"
class Entity : public Shape {
private:
	int radius;
public:
	Entity(){}
	Entity(int radius, int edgesize);
	Entity(int radius, int edgesize, sf::Vector2f pos);

	sf::Vector2f pos;
	sf::Vector2f vel;

	virtual void move() = 0;
};


#endif