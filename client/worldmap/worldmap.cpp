#include "worldmap.hpp"

//Testing.purposes
WorldMap::WorldMap() {
}
void WorldMap::addPlayer(int id) {
	entities[id] = std::unique_ptr<Entity>(new Player());
}
void WorldMap::tick() {
	for (auto const &entity : entities) {
		entity.second->tick();
	}
}
void WorldMap::draw(sf::RenderWindow &window) {
	for (auto const &entity : entities) {
		entity.second->draw(window);
	}
}

bool WorldMap::idExists(int id) {
	if ( entities.find(id) == entities.end() ) {
		return false;
	}
	return true;
}

void WorldMap::processEntity(int id, int x, int y) {
	if (!idExists(id)) {
		entities[id] = std::unique_ptr<Entity>(new Mob(sf::Vector2f(x, y), sf::Vector2f(0, 0)));
		std::cout << "generated entity at " << x << " " << y << " " << entities.size() << std::endl;
	}
	else {
		entities[id]->tick();
	}
}