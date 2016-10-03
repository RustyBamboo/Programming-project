/*

	This will be the main Map class that processes all the entities and updates everything.

*/

#ifndef WORLD_MAP_HPP
#define WORLD_MAP_HPP
#include "../include.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/bullet.hpp"
#include "../entities/mob.hpp"
#include <memory>

//Testing.
class WorldMap {

private:
	std::vector<std::unique_ptr<Entity> > entities;

public:
	WorldMap();
	void tick();
	void draw(sf::RenderWindow &window);

};

#endif