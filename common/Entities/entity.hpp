#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

//Most basic form of an entity. Contains an object (such as a Polygon or a Ray)
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f & v);
sf::Packet& operator >>(sf::Packet& packet,sf::Vector2f & v);
class Entity {
public:
    enum EntityType {
			polygon,
			rectangle
		};
    Entity(sf::Vector2f  &pos, sf::Vector2f &vel, EntityType t);
    Entity();
		virtual void draw(sf::RenderWindow &window) = 0;
		void setPosition(const sf::Vector2f &pos);
		bool isCollided(Entity &e); //Need this written
    void tick(); //We need tick functions to be synced (get diff in time)
    
		Entity& operator << (sf::Packet& packet);

		Entity& operator >> (sf::Packet& packet);
		
		void setPosition(sf::Vector2f  p);
		sf::Vector2f  getPosition();
		void setVelocity(sf::Vector2f  v);
		sf::Vector2f  getVelocity();
private:
		sf::Vector2f position;
		sf::Vector2f velocity;
protected:
		EntityType type;
};
