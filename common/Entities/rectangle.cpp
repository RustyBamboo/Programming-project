#include "rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f &pos, sf::Vector2f &vel, sf::Vector2f size, float angle, uint32_t owner) :
    Entity(pos, vel, Entity::EntityType::rectangle), owned_by(owner)
{
    shape.setSize(size);
    shape.setRotation(angle);
}
Rectangle::Rectangle(): Entity(Entity::EntityType::rectangle) {}

void Rectangle::draw(sf::RenderWindow &window) {
    // shape.setOutlineColor(sf::Color::Red);
    // shape.setOutlineThickness(5);
    //  printf("Rect Position=(%f,%f) Size=(%f,%f)\n", shape.getPosition().x, shape.getPosition().y,shape.getSize().x, shape.getSize().y);
    window.draw(shape);
}

void Rectangle::setView(sf::RenderWindow &window) {
    sf::View view;
    view.setCenter(getCenter());
    window.setView(view);
}

sf::Vector2f Rectangle::getCenter() {
    return sf::Vector2f(getPosition().x + shape.getSize().x, getPosition().y + shape.getSize().y);
}

std::vector<sf::Vector2f> Rectangle::getEdgePoints() {}

sf::FloatRect Rectangle::getGlobalBounds() {
    return shape.getGlobalBounds();
}
uint32_t Rectangle::getOwner()
{
    return owned_by;
}
void Rectangle::tick()
{
    Entity::tick();
    shape.setPosition(getPosition());
}
void Rectangle::toPacket(sf::Packet& packet)
{
    Entity::toPacket(packet);
    shape.setPosition(getPosition());
    packet << owned_by;
    packet << shape.getSize();
    packet << (float) shape.getRotation();
    //  printf("RECT OWNEDBY=%d\n", owned_by);
    //  printf("Rect PACKET=%u Position=(%f,%f) Size=(%f,%f)\n",packet.getDataSize(), shape.getPosition().x, shape.getPosition().y,shape.getSize().x, shape.getSize().y);
}
void Rectangle::fromPacket(sf::Packet& packet)
{
    //  printf("from\n");
    Entity::fromPacket(packet);
    sf::Vector2f size;
    float angle;
    packet >> owned_by;
    packet >> size;
    packet >> angle;
    // printf("RECT OWNEDBY=%d\n", owned_by);
    //  printf("HMM POSITION(%f,%f) (%f,%f) %f\n", getPosition().x, getPosition().y, size.x, size.y, angle);
    shape.setRotation(angle);
    shape.setSize(size);
    shape.setPosition(getPosition());
    //  printf("Rect PACKET=%u Position=(%f,%f) Size=(%f,%f)\n",packet.getDataSize(), shape.getPosition().x, shape.getPosition().y,shape.getSize().x, shape.getSize().y);
}
