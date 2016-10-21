#include "polygon.hpp"

Polygon::Polygon(sf::Vector2f pos, sf::Vector2f vel,int size, int edges) :
	Entity(pos,vel,Entity::EntityType::polygon),
	shape(size, edges)
{
	
}
Polygon::Polygon()
{
	
}
void Polygon::draw(sf::RenderWindow &window) {
  shape.setPosition(getPosition());
	window.draw(shape);
}

Polygon& Polygon::operator << (sf::Packet& packet)
{

    sf::Uint32 points;
    float radius;
    *(Entity*) this << packet;
    packet >> radius;
    packet >> points;
    shape.setRadius(radius);
    shape.setPointCount(points);
    printf("Unloading polygon packet Velocity=(%f,%f) Sides=%d",getVelocity().x,getVelocity().y,shape.getPointCount());
}

Polygon& Polygon::operator >>(sf::Packet& packet)
{
    *(Entity*) this >> packet;
    packet << shape.getRadius();
    packet << (sf::Uint32) shape.getPointCount();
    printf("Sending polygon packet Velocity=(%f,%f) Sides=%d",getVelocity().x,getVelocity().y,shape.getPointCount());
}	
