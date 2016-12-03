#include "worldmap.hpp"

double WorldMap::ZOOM_FACTOR = 1.0;
int WorldMap::height = 900;
int WorldMap::width = 1200;

bool WorldMap::isOutOfMap(sf::FloatRect rect)
{
  return rect.left+rect.width <0
      || rect.left -rect.width > width*ZOOM_FACTOR
      || rect.top+rect.height < 0
      || rect.top-rect.height > height*ZOOM_FACTOR;
}
WorldMap::WorldMap()
{
	last_id = 0;
}
bool WorldMap::hasEntity(ID_TYPE id)
{
  auto search = entities.find(id);
  return search != entities.end();
}
void WorldMap::addEntity(ID_TYPE id, Entity* e)
{
	auto search = entities.find(id);
	if (search != entities.end()) {
		throw std::runtime_error("Entity already added");
	}
	else {
    //  printf("ADDING NEW ENTITY ID=%d TYPE=%d\n", id, e->type);
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
  //  printf("Erased %d\n", entities.erase(id));
  entities.erase(id);
}
WorldMap::ID_TYPE WorldMap::newEntity(Entity* e)
{
	last_id++;
  //  printf("CREATING NEW ENTITY ID=%d TYPE=%d\n", last_id, e->type);
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
int WorldMap::checkOutOfMap(sf::Packet &packet)
{
  int holder = 0;
  for (it_type e = entities.begin(); e != entities.end();)
  {
    if (e->second->type == Entity::rectangle && isOutOfMap(e->second->getGlobalBounds()))
    {
      //  printf("DELETING OUT OF BOUNDS BULLET %u\n", e->first);
      UpdatePacket update(UpdatePacket::REMOVE_ENTITY,  e->first);
      packet << update;
      holder++;
      e = entities.erase(e);
    } else e++;
  }
  return holder;
}
int WorldMap::checkCollisions(sf::Packet &packet, std::stack<sf::Color>& colors)
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
            if (hasEntity(ownerID)) {
							UpdatePacket updatePlayer(UpdatePacket::UPDATE_POLYGON, ownerID);
							packet << updatePlayer;
							Polygon* p = (Polygon*) getEntity(ownerID);
							p->addEdge();
							p->toPacket(packet);
							holder++;
						}

						{
							Polygon* p = (Polygon*) iteratorA->second.get();
              if (p->getPointCount() <= 3)
              {
                  colors.push(p->getColor());
                  UpdatePacket update(UpdatePacket::REMOVE_ENTITY, iteratorA->first);
                  packet << update;
                  holder++;
                  iteratorA = entities.erase(iteratorA);
                  {
                    UpdatePacket update(UpdatePacket::REMOVE_ENTITY,  iteratorB->first);
                    packet << update;
                    holder++;
                    iteratorB = entities.erase(iteratorB);
                  }
                  goto outer;
              } else {
                  p->deleteEdge();
                  UpdatePacket update(UpdatePacket::UPDATE_POLYGON, iteratorA->first);
                  packet << update;
                  p->toPacket(packet);
                  holder++;
              }
						}
						// iteratorB->second->setPosition(sf::Vector2f(10000000, 100000));
						// iteratorB->second->setVelocity(sf::Vector2f(0, 0));
            {
              //  printf("DELETING BULLETB ID=%u\n", iteratorB->first);
              UpdatePacket update(UpdatePacket::REMOVE_ENTITY,  iteratorB->first);
							packet << update;
							holder++;
              iteratorB = entities.erase(iteratorB);
            }

					}
					else if (iteratorA->second->type == Entity::rectangle && iteratorB->second->type == Entity::polygon) {
						auto ownerID = ((Rectangle*) iteratorA->second.get())->getOwner();
						if (iteratorB->first == ownerID) {
              iteratorB++;
              continue;
            }
						if (hasEntity(ownerID)) {
							UpdatePacket updatePlayer(UpdatePacket::UPDATE_POLYGON, ownerID);
							packet << updatePlayer;
							Polygon* p = (Polygon*) getEntity(ownerID);
							p->addEdge();
							p->toPacket(packet);
							holder++;
						}
						{
							Polygon* p = (Polygon*) iteratorB->second.get();
              if (p->getPointCount() <= 3)
              {
                  colors.push(p->getColor());
                  UpdatePacket update(UpdatePacket::REMOVE_ENTITY, iteratorB->first);
                  packet << update;
                  holder++;
                  iteratorB = entities.erase(iteratorB);
              } else {
                  p->deleteEdge();
                  UpdatePacket update(UpdatePacket::UPDATE_POLYGON, iteratorB->first);
                  packet << update;
                  p->toPacket(packet);
                  holder++;
              }
						}
            {
              UpdatePacket update(UpdatePacket::REMOVE_ENTITY,  iteratorA->first);
							packet << update;
							holder++;
              iteratorA = entities.erase(iteratorA);
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

