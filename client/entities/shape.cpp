#include "shape.h"

Shape::Shape(int size, int edgesize) : shape(size, edgesize) {}
Shape::Shape(int size, int edgesize, sf::Vector2f pos) : shape(size, edgesize) {
	shape.setPosition(pos);
}
void Shape::setColor(sf::Color color) {
	shape.setFillColor(color);
}

void Shape::rotate(float angle) {
	shape.setRotation(angle);
}

void Shape::draw(sf::RenderWindow &window) {
	window.draw(shape);
}