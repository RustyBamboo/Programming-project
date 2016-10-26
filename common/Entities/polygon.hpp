#pragma once
#include "entity.hpp"

class Polygon : public Entity {
private:
	sf::CircleShape shape;
public:
	Polygon(sf::Vector2f pos, sf::Vector2f vel,int size, int edges);
	Polygon();
	virtual void draw(sf::RenderWindow &window);
    virtual void setView(sf::RenderWindow &window);
    virtual sf::Vector2f getCenter();

	Polygon& operator << (sf::Packet& packet);

	Polygon& operator >>(sf::Packet& packet);

};
