#ifndef SHAPE_H
#define SHAPE_H
#include "../include.h"
class Shape {
private:
	sf::CircleShape shape;
public:
	Shape(){}
	Shape(int radius, int edgesize);
	Shape(int radius, int edgesize, sf::Vector2f pos);
	void setColor(sf::Color color);
	void rotate(float angle);
	void draw(sf::RenderWindow &window);
};
#endif 