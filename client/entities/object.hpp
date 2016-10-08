#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../include.hpp"

//Abstract class that allows different types of shapes (and custom images)
class Object {
public:
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void setPosition(const sf::Vector2f &pos) = 0;
	virtual void setColor(sf::Color color) = 0;
	bool isCollided(Object &obj); //Need this written in server prob

};

#endif