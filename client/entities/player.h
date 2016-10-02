#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../include.hpp"

class Player : public Entity{
public:
	Player();
	void move();
};

#endif