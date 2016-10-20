#include "rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f &pos, sf::Vector2f &vel,sf::Vector2f size) :
	Entity(pos,vel,Entity::EntityType::rectangle)
{
	shape.setSize(size);
}

void Rectangle::draw(sf::RenderWindow &window) {
	window.draw(shape);
}
