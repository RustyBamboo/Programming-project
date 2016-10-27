#include "worldmap.hpp"

WorldMap::WorldMap()
{
	last_id = 0;
}
void WorldMap::addEntity(ID_TYPE id,Entity* e)
{
	last_id = id;
	entities.insert(std::pair<ID_TYPE,std::unique_ptr<Entity> >(id,std::unique_ptr<Entity>(e)) );
} 
Entity* WorldMap::getEntity(ID_TYPE id)
{
	auto search = entities.find(id);
	if(search != entities.end()) {
		return search->second.get();
	}
	else {
		std::cout << "Not found\n";
    return NULL;
	}
}
void WorldMap::removeEntity(ID_TYPE id)
{
	auto search = entities.find(id);
	if(search != entities.end()) {
		entities.erase(search);
	}
	else {
		std::cout << "Not found\n";
	}	
}
WorldMap::ID_TYPE WorldMap::newEntity(Entity* e)
{
	last_id++;
	entities.insert(std::pair<ID_TYPE,std::unique_ptr<Entity> >(last_id,std::unique_ptr<Entity>(e)) );
	return last_id;
}    
void WorldMap::draw(sf::RenderWindow &window)
{
#ifdef DO_DEBUG
  printf("World Map Drawing %lu entities\n",entities.size());
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
	for (auto const &entity : entities)
	{
		entity.second->isCollided(entity.second);
	}
}

