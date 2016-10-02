

#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H

#include "cscreen.h"

#include <SFML/Graphics.hpp>
#include <memory>

#include "screengame.h"

#include "../entities/entity.h"
#include "../entities/player.h"

class ScreenGame : public CScreen
{
private:
	std::unique_ptr<Entity> ent;
public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif