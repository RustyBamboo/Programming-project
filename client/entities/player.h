#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../include.hpp"
#include "polygon.hpp"
class Player : public Entity{
public:
	Player();
	virtual void move();
};

#endif