#pragma once
#include "entity.hpp"

class Polygon : public Entity {
private:
    sf::CircleShape shape;
public:
    Polygon(sf::Vector2f pos, sf::Vector2f vel, int size, int edges, sf::Color color);
    Polygon();
    virtual void draw(sf::RenderWindow &window);
    virtual void setView(sf::RenderWindow &window, sf::View &view);

    virtual sf::Vector2f getCenter();
    virtual std::vector<sf::Vector2f> getEdgePoints();
    virtual sf::FloatRect getGlobalBounds();
    virtual void tick();

    uint getPointCount();
    void addEdge();
    void deleteEdge();
    void toPacket(sf::Packet& packet);
    void fromPacket(sf::Packet& packet);
};
