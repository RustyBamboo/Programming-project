#include "worldmap.hpp"

WorldMap::WorldMap()
{
	last_id = 0;
}
void WorldMap::addEntity(ID_TYPE id, Entity* e)
{
  	auto search = entities.find(id);
	if (search != entities.end()) {
		throw std::runtime_error("Entity already added");
	}
	else {
	last_id = id;
	entities.insert(std::pair<ID_TYPE, std::unique_ptr<Entity> >(id, std::unique_ptr<Entity>(e)) );
	}
}
Entity* WorldMap::getEntity(ID_TYPE id)
{
	auto search = entities.find(id);
	if (search != entities.end()) {
		return search->second.get();
	}
	else {
		throw std::runtime_error("Entity not found");
	}
}
void WorldMap::removeEntity(ID_TYPE id)
{
	auto search = entities.find(id);
	if (search != entities.end()) {
		entities.erase(search);
	}
	else {
		std::cout << "Not found\n";
	}
}
WorldMap::ID_TYPE WorldMap::newEntity(Entity* e)
{
	last_id++;
	entities.insert(std::pair<ID_TYPE, std::unique_ptr<Entity> >(last_id, std::unique_ptr<Entity>(e)) );
	return last_id;
}
void WorldMap::draw(sf::RenderWindow &window)
{
#ifdef DO_DEBUG
	printf("World Map Drawing %lu entities\n", entities.size());
#endif
	for (auto const &entity : entities)
	{
		entity.second->draw(window);
	}
}
void WorldMap::tick()
{
	for (auto const &entity : entities)
	{
		entity.second->tick();
	}
}
void WorldMap::checkCollisions()
{
	// typedef std::map<ID_TYPE, std::unique_ptr<Entity> >::iterator it_type;
	// for (it_type iteratorA = entities.begin(); iteratorA != entities.end(); iteratorA++) {
	// 	it_type iteratorB = iteratorA;
	// 	for (iteratorB++; iteratorB != entities.end(); iteratorB++) {
	// 		if (iteratorA->second != iteratorB->second) {
	// 			if (iteratorA->second->isCollided(iteratorB->second)) {
	// 				std::cout << iteratorA->second->type << " " << iteratorB->second->type << std::endl;
	// 			}
	// 		}
	// 	}
	// 	// iterator->first = key
	// 	// iterator->second = value
	// 	// Repeat if you also want to iterate through the second map.
	// }
	for (auto const &entityA : entities)
	{
		for (auto const &entityB : entities)
		{
			if (entityA.second != entityB.second)
				if (entityA.second->isCollided(entityB.second)) {
					//  if(entityA.second->type == Entity::polygon) std::cout << "polygon" << std::endl;
				}
		}
	}
}

