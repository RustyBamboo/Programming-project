#include "entity.hpp"

Entity::Entity(sf::Vector2f &pos, sf::Vector2f &vel, EntityType t) :
		position(pos),
		velocity(vel),
		type(t)
{

}
Entity::Entity()
{
}
//Updates the entity, processes the Move function, adds velocity, and updates the Object
void Entity::tick() {
    position += velocity;
}
Entity& Entity::operator << (sf::Packet& packet)
{
		packet >> position;
		packet >> velocity;
}
Entity& Entity::operator >> (sf::Packet& packet)
{
		packet << position;
		packet << velocity;
}	
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v)
{
	return packet << v.x << v.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v)
{
    return packet >> v.x >> v.y;
}
