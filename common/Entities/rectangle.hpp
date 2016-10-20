#pragma once
#include "entity.hpp"

class Rectangle : public Entity {
private:
	sf::RectangleShape shape;
public:
	Rectangle(sf::Vector2f &pos, sf::Vector2f &vel,sf::Vector2f size);
	virtual void draw(sf::RenderWindow &window);

};
