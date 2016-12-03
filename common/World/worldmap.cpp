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
    printf("ADDING NEW ENTITY ID=%d TYPE=%d\n", id, e->type);
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
  printf("Erased %d\n", entities.erase(id));
}
WorldMap::ID_TYPE WorldMap::newEntity(Entity* e)
{
	last_id++;
  printf("CREATING NEW ENTITY ID=%d TYPE=%d\n", last_id, e->type);
	entities.insert(std::pair<ID_TYPE, std::unique_ptr<Entity> >(last_id, std::unique_ptr<Entity>(e)) );
	return last_id;
}
void WorldMap::draw(sf::RenderWindow &window)
{
//  #ifdef DO_DEBUG
	//  printf("World Map Drawing %lu entities\n", entities.size());
//  #endif
  for (it_type e = entities.begin(); e != entities.end(); e++)
	{
		e->second->draw(window);
	}
}
void WorldMap::tick()
{
  for (it_type e = entities.begin(); e != entities.end(); e++)
	{
		e->second->tick();
	}
}
int WorldMap::checkCollisions(sf::Packet &packet)
{
	int holder = 0;
	outer: for (it_type iteratorA = entities.begin(); iteratorA != entities.end();) {
		it_type iteratorB = iteratorA;
		for (iteratorB++; iteratorB != entities.end();) {
			if (iteratorA->second != iteratorB->second) {
				if (iteratorA->second->isCollided(iteratorB->second)) {
					if (iteratorA->second->type == Entity::polygon && iteratorB->second->type == Entity::rectangle) {
						auto ownerID = ((Rectangle*) iteratorB->second.get())->getOwner();
						if (iteratorA->first == ownerID) {
              iteratorB++;
              continue;
            }
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
            {
              iteratorB = entities.erase(iteratorB);
              printf("DELETING BULLETB ID=%u\n", iteratorB->first);
              UpdatePacket update(UpdatePacket::REMOVE_ENTITY,  iteratorB->first);
							packet << update;
							holder++;
            }

					}
					else if (iteratorA->second->type == Entity::rectangle && iteratorB->second->type == Entity::polygon) {
						auto ownerID = ((Rectangle*) iteratorA->second.get())->getOwner();
						if (iteratorB->first == ownerID) {
              iteratorB++;
              continue;
            }
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
            {
              iteratorA = entities.erase(iteratorA);
              printf("DELETING BULLETA ID=%u\n", iteratorA->first);
              UpdatePacket update(UpdatePacket::REMOVE_ENTITY,  iteratorA->first);
							packet << update;
							holder++;
              goto outer;
            }
					} else iteratorB++;
				} else iteratorB++;
			} else iteratorB++;
		}
    iteratorA++;
	}
	return holder;
}

