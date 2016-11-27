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

void Polygon::setView(sf::RenderWindow &window) {
    sf::View view;
    view.setCenter(getCenter());
    window.setView(view);
}

sf::Vector2f Polygon::getCenter() {
    return sf::Vector2f(getPosition().x + shape.getRadius(), getPosition().y + shape.getRadius());
}

std::vector<sf::Vector2f> Polygon::getEdgePoints() {
    std::vector<sf::Vector2f> v;
    for(unsigned int i = 0; i < shape.getPointCount(); ++i) {
        v.push_back(getPosition() + shape.getPoint(i));
    }
    return v;
}
void Polygon::fromPacket(sf::Packet& packet)
{
    Entity::fromPacket(packet);
    sf::Uint32 points;
    float radius;
    packet >> radius;
    packet >> points;
    shape.setRadius(radius);
    shape.setPointCount(points);
    printf("Unloading polygon packet Velocity=(%f,%f) Sides=%d",getVelocity().x,getVelocity().y,shape.getPointCount());
}
void Polygon::toPacket(sf::Packet& packet)
{
    Entity::toPacket(packet);
    packet << shape.getRadius();
    packet << (sf::Uint32) shape.getPointCount();
    printf("Sending polygon packet Velocity=(%f,%f) Sides=%d",getVelocity().x,getVelocity().y,shape.getPointCount());
}	
