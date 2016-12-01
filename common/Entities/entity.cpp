#include "entity.hpp"
#include "../include.hpp"
Entity::Entity(sf::Vector2f &pos, sf::Vector2f &vel, EntityType t) :
    position(pos),
    velocity(vel),
    type(t)
{

}
Entity::Entity() : type(entity)
{
}


//Updates the entity, processes the Move function, adds velocity, and updates the Object
void Entity::tick() {
    position += velocity;
}
void Entity::setPosition(sf::Vector2f p)
{
    position = p;
}
sf::Vector2f Entity::getPosition()
{
    return position;
}
void Entity::setVelocity(sf::Vector2f v)
{
    velocity = v;
}
sf::Vector2f Entity::getVelocity()
{
    return velocity;
}
void Entity::fromPacket(sf::Packet& packet)
{
    packet >> position;
    packet >> velocity;
}
void Entity::toPacket(sf::Packet& packet)
{
    packet << position;
    packet << velocity;
}
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& v)
{
    //~ float x = v.x;
    //~ float y = v.y;
    //~ printf("Sending x=%f y=%f\n",x,y);
    packet << v.x << v.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& v)
{
    //~ float x = 0;
    //~ float y = 0;
    packet >> v.x >> v.y;
    //~ printf("Loaded x=%f y=%f\n",x,y);
    //~ v = sf::Vector2f(x,y);
}


bool Entity::isCollided(std::unique_ptr<Entity> const &e) { //Seperating Axis Theorem
    return getLocalBounds().intersects(e->getLocalBounds());

}
