#include "ray.hpp"

Ray::Ray(int width, int height) {
	shape.setSize(sf::Vector2f(width, height));
}

void Ray::draw(sf::RenderWindow &window) {
	window.draw(shape);
}

void Ray::setPosition(const sf::Vector2f &pos) {
	shape.setPosition(pos);
}


void Ray::setColor(sf::Color color) {
	shape.setFillColor(color);
}