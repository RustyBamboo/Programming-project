#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "object.hpp"

class Polygon : public Object {
private:
	sf::CircleShape shape;

public:
	Polygon(int radius, int edges);
	virtual void draw(sf::RenderWindow &window);
	virtual void setPosition(const sf::Vector2f &pos);
	virtual void setColor(sf::Color color);

};

#endif