#pragma once
#include "entity.hpp"

class Polygon : public Entity {
private:
	sf::CircleShape shape;
public:
	Polygon(sf::Vector2f pos, sf::Vector2f vel,int size, int edges);
	Polygon();
	virtual void draw(sf::RenderWindow &window);
	
	Polygon& operator << (sf::Packet& packet)
	{
			sf::Uint32 points;
			float radius;
			*(Entity*) this << packet;
			packet >> radius;
			packet >> points;
      shape.setRadius(radius);
      shape.setPointCount(points);
	}

	Polygon& operator >>(sf::Packet& packet)
	{
			*(Entity*) this >> packet;
			packet << shape.getRadius();
			packet << (sf::Uint32) shape.getPointCount();
	}	

};
