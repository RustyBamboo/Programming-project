#include "mob.hpp"

Mob::Mob(sf::Vector2f p, sf::Vector2f v) {
	pos = p;
	vel = v;
	obj = new Polygon(30, 5);
}
Mob::Mob(int size, int edges, sf::Vector2f p, sf::Vector2f v) {
	pos = p;
	vel = v;
	obj = new Polygon(size, edges);
	obj->setColor(sf::Color::Red);
}
void Mob::move() {
	pos+=vel;
}