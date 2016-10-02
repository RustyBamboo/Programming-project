#include "entity.h"

Entity::Entity(int radius, int edgesize) : Shape (radius, edgesize) {}
Entity::Entity(int radius, int edgesize, sf::Vector2f pos) : Shape(radius, edgesize, pos) {
	this->pos = pos;
	this->vel = sf::Vector2f(0,0);
}
