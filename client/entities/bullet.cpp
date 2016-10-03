#include "bullet.hpp"

Bullet::Bullet(sf::Vector2f p, sf::Vector2f v) {
	pos = p;
	vel = v;
	obj = new Ray(10,50);
}
void Bullet::move() {
	pos+=vel;
}