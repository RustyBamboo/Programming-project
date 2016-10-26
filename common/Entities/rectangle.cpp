#include "rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f &pos, sf::Vector2f &vel,sf::Vector2f size) :
	Entity(pos,vel,Entity::EntityType::rectangle)
{
	shape.setSize(size);
}

void Rectangle::draw(sf::RenderWindow &window) {
	window.draw(shape);
}

void Rectangle::setView(sf::RenderWindow &window) {
    sf::View view;
    view.setCenter(getCenter());
    window.setView(view);
}

sf::Vector2f Rectangle::getCenter() {
    return sf::Vector2f(getPosition().x + shape.getSize().x, getPosition().y + shape.getSize().y);
}

