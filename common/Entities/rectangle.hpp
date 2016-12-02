#pragma once
#include "entity.hpp"

class Rectangle : public Entity {
private:
    sf::RectangleShape shape;
    uint32_t owned_by;
public:
    Rectangle(sf::Vector2f &pos, sf::Vector2f &vel, sf::Vector2f size, float angle, uint32_t owner, sf::Color color);
    Rectangle();
    virtual void draw(sf::RenderWindow &window);
    virtual void setView(sf::RenderWindow &window, sf::View &view);

    virtual sf::Vector2f getCenter();
    virtual std::vector<sf::Vector2f> getEdgePoints();
    virtual sf::FloatRect getGlobalBounds();
    virtual void tick();
    uint32_t getOwner();


    void toPacket(sf::Packet& packet) override;
    void fromPacket(sf::Packet& packet) override;
};
