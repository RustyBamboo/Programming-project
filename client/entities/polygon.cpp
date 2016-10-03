#include "polygon.hpp"

Polygon::Polygon(int size, int edges) : shape(size, edges) {}


void Polygon::draw(sf::RenderWindow &window) {
	window.draw(shape);
}

void Polygon::setPosition(const sf::Vector2f &pos) {
	shape.setPosition(pos);
}

void Polygon::setColor(sf::Color color) {
	shape.setFillColor(color);
}