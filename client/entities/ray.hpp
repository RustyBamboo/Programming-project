#ifndef RAY_HPP
#define RAY_HPP

#include "object.hpp"

class Ray : public Object{
private:
	sf::RectangleShape shape;
public:
	Ray(int width, int height);
	virtual void draw(sf::RenderWindow &window);
	virtual void setPosition(const sf::Vector2f &pos);
	virtual void setColor(sf::Color color);

};

#endif