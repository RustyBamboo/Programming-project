/*
	Class to manage the actual game. 
*/

#ifndef SCREEN_GAME_HPP
#define SCREEN_GAME_HPP

#include "cscreen.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

#include "screengame.hpp"

#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/bullet.hpp"
#include "../entities/mob.hpp"

#include "../worldmap/worldmap.hpp"

class ScreenGame : public CScreen
{
private:
	std::unique_ptr<Entity> ray;
	std::unique_ptr<Entity> mob;

	WorldMap worldMap;

public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif