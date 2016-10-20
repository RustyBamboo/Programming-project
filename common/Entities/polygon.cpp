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
