#include "worldmap.hpp"

//Testing.purposes
WorldMap::WorldMap() {
	entities.push_back(std::unique_ptr<Entity>(new Player()));
	for(int i = 0 ; i < 10; ++i) {
		entities.push_back(std::unique_ptr<Entity>(new Mob(35, i, sf::Vector2f(i*70,0), sf::Vector2f(0,0))));
	}
}
void WorldMap::tick() {
	for (int i =0 ;i < entities.size(); i++) {
		entities[i]->tick();
	}
}
void WorldMap::draw(sf::RenderWindow &window) {
	for (int i =0 ;i < entities.size(); i++) {
		entities[i]->draw(window);
	}
}