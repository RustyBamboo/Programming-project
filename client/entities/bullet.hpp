#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp" 
#include "ray.hpp"


class Bullet : public Entity {

public:
	Bullet(sf::Vector2f p, sf::Vector2f v);
	virtual void move();

};

#endif