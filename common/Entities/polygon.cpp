#include "polygon.hpp"

Polygon::Polygon(sf::Vector2f pos, sf::Vector2f vel, int size, int edges, sf::Color color) :
    Entity(pos, vel, Entity::EntityType::polygon),
    shape(size, edges)
{
    shape.setFillColor(color);
}
Polygon::Polygon() : Entity(Entity::EntityType::polygon)
{

}
void Polygon::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
void Polygon::setView(sf::RenderWindow &window, sf::View &view) {
    view.setCenter(getCenter());
    window.setView(view);
}
sf::Color Polygon::getColor()
{
  return shape.getFillColor();
}
sf::Vector2f Polygon::getCenter() {
    return sf::Vector2f(getPosition().x + shape.getRadius(), getPosition().y + shape.getRadius());
}

std::vector<sf::Vector2f> Polygon::getEdgePoints() {
    std::vector<sf::Vector2f> v;
    for (unsigned int i = 0; i < shape.getPointCount(); ++i) {
        v.push_back(shape.getPoint(i));
    }
    return v;
}

sf::FloatRect Polygon::getGlobalBounds() {
    return shape.getGlobalBounds();
}

void Polygon::addEdge() {
    if (shape.getPointCount() < 20)
        shape.setPointCount(shape.getPointCount() + 1);
}
void Polygon::deleteEdge() {
    if (shape.getPointCount() > 3)
        shape.setPointCount(shape.getPointCount() - 1);
}
uint Polygon::getPointCount() {
    return shape.getPointCount();
}
inline sf::Packet& operator <<(sf::Packet& packet, const sf::Color& c)
{
    packet << c.r << c.g << c.b << c.a;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::Color& c)
{
    packet >> c.r >> c.g >> c.b >> c.a;
}

void Polygon::fromPacket(sf::Packet& packet)
{
    Entity::fromPacket(packet);
    shape.setPosition(getPosition());
    sf::Uint32 points;
    float radius;
    sf::Color color;
    packet >> radius;
    packet >> points;
    packet >> color;
    shape.setRadius(radius);
    shape.setPointCount(points);
    shape.setFillColor(color);
}
void Polygon::tick()
{
    Entity::tick();
    shape.setPosition(getPosition());
}
void Polygon::toPacket(sf::Packet& packet)
{
    Entity::toPacket(packet);
    packet << shape.getRadius();
    packet << (sf::Uint32) shape.getPointCount();
    packet << shape.getFillColor();
}

