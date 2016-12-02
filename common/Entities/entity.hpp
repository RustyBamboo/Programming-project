#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include "../gamemath.hpp"

//Most basic form of an entity. Contains an object (such as a Polygon or a Ray)
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f & v);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f & v);
class Entity {
public:
    enum EntityType {
        polygon,
        rectangle,
        entity
    };
    Entity(sf::Vector2f  &pos, sf::Vector2f &vel, EntityType t);
    Entity(EntityType t);
    Entity();
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void setView(sf::RenderWindow &window) = 0;

    virtual sf::Vector2f getCenter() = 0;
    virtual std::vector<sf::Vector2f> getEdgePoints() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;

    void setPosition(const sf::Vector2f &pos);
    bool isCollided(std::unique_ptr<Entity> const &e); //Need this written
    void tick(); //We need tick functions to be synced (get diff in time)
    virtual void toPacket(sf::Packet& packet);
    virtual void fromPacket(sf::Packet& packet);

    void setPosition(sf::Vector2f  p);
    sf::Vector2f  getPosition();
    void setVelocity(sf::Vector2f  v);
    sf::Vector2f  getVelocity();
    const EntityType type;
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
};
