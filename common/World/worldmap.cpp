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
int WorldMap::checkCollisions(sf::Packet &packet)
{
	int holder = 0;

	typedef std::map<ID_TYPE, std::unique_ptr<Entity> >::iterator it_type;
	for (it_type iteratorA = entities.begin(); iteratorA != entities.end(); iteratorA++) {
		it_type iteratorB = iteratorA;
		for (iteratorB++; iteratorB != entities.end(); iteratorB++) {
			if (iteratorA->second != iteratorB->second) {

				if (iteratorA->second->isCollided(iteratorB->second)) {
					if (iteratorA->second->type == Entity::polygon && iteratorB->second->type == Entity::rectangle) {
						auto ownerID = ((Rectangle*) iteratorB->second.get())->getOwner();

						if (iteratorA->first == ownerID) continue;

						{
							UpdatePacket updatePlayer(UpdatePacket::UPDATE_POLYGON, ownerID);
							packet << updatePlayer;
							Polygon* p = (Polygon*) getEntity(ownerID);
							p->addEdge();
							p->toPacket(packet);
							holder++;
						}

						{
							UpdatePacket update(UpdatePacket::UPDATE_POLYGON, iteratorA->first);
							packet << update;
							Polygon* p = (Polygon*) iteratorA->second.get();
							p->deleteEdge();
							p->toPacket(packet);
							holder++;
						}
						// iteratorB->second->setPosition(sf::Vector2f(10000000, 100000));
						// iteratorB->second->setVelocity(sf::Vector2f(0, 0));


					}
					if (iteratorA->second->type == Entity::rectangle && iteratorB->second->type == Entity::polygon) {
						auto ownerID = ((Rectangle*) iteratorA->second.get())->getOwner();

						if (iteratorB->first == ownerID) continue;

						{
							UpdatePacket updatePlayer(UpdatePacket::UPDATE_POLYGON, ownerID);
							packet << updatePlayer;
							Polygon* p = (Polygon*) getEntity(ownerID);
							p->addEdge();
							p->toPacket(packet);
							holder++;
						}

						{
							UpdatePacket update(UpdatePacket::UPDATE_POLYGON, iteratorB->first);
							packet << update;
							Polygon* p = (Polygon*) iteratorB->second.get();
							p->deleteEdge();
							p->toPacket(packet);
							holder++;
						}
						// iteratorA->second->setPosition(sf::Vector2f(10000000, 100000));
						// iteratorA->second->setVelocity(sf::Vector2f(0, 0));
					}
				}

			}
		}
	}
	return holder;

// for (auto const &entityA : entities)
// {
// 	for (auto const &entityB : entities)
// 	{
// 		if (entityA.second != entityB.second)
// 			if (entityA.second->isCollided(entityB.second)) {
// 				//  if(entityA.second->type == Entity::polygon) std::cout << "polygon" << std::endl;
// 			}
// 	}
// }
}

