#include "entity.hpp"
#include "../include.hpp"
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
    //Hate math.
    std::vector<sf::Vector2f> thisEdgePoint = getEdgePoints(); //this will be incorrect for now cause server does not update polygons
    // for(unsigned int i = 0; i < thisEdgePoint.size(); ++i) {
    //     std::cout << thisEdgePoint[i].x << " " << thisEdgePoint[i].y << std::endl;
    // }
    std::vector<sf::Vector2f> eEdgePoint = e->getEdgePoints();

    std::vector<sf::Vector2f> eNormals = gmath::getAllNormals(eEdgePoint);
    std::vector<sf::Vector2f> allNormals = gmath::getAllNormals(thisEdgePoint);
    allNormals.insert(std::end(allNormals), std::begin(eNormals), std::end(eNormals));


    // sf::Vector2f minPointA(10000000, 10000000);
    // sf::Vector2f maxPointA(-10000000, -10000000);

    // sf::Vector2f minPointB(10000000, 10000000);
    // sf::Vector2f maxPointB(-10000000, -10000000);

    float minSPointA = 1000000, maxSPointA = -1000000;
    float minSPointB = 1000000, maxSPointB = -1000000;



    for (const sf::Vector2f &normal : allNormals) {
        for (const sf::Vector2f &tEP : thisEdgePoint) {
            float proj = gmath::scalarProjection(tEP, normal);
            if (proj > maxSPointA) maxSPointA = proj;
            if (proj < minSPointA) minSPointA = proj;
        }
        for (const sf::Vector2f &tEP : eEdgePoint) {
            float proj = gmath::scalarProjection(tEP, normal);
            if (proj > maxSPointB) maxSPointB = proj;
            if (proj < minSPointB) minSPointB = proj;
        }
        if (minSPointB > maxSPointA || minSPointA > maxSPointB) {
            std::cout << "collision" << std::endl;
            return true;
        }
    }
    return false;
}
