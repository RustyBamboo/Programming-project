#include "worldmap.hpp"

//Testing.purposes
WorldMap::WorldMap() {
}
void WorldMap::addPlayer(int id) {
	playerID = id;
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
		entities[id]->pos.x = x;
		entities[id]->pos.y = y;
	}
}

void WorldMap::sendInfo(sf::UdpSocket &udpSocket, sf::IpAddress address, unsigned short port ) {
    std::string id(6, ' ');
    std::string xpos(9, ' ');
    std::string ypos(9, ' ');
    id.replace(0, 3, std::to_string(playerID));
    std::string X(std::to_string((int)entities[playerID]->pos.x));
    std::string Y(std::to_string((int)entities[playerID]->pos.y));
    xpos.replace(0, X.size(), X);
    ypos.replace(0, Y.size(), Y);

    std::string result;
    result = id + xpos + ypos;
    udpSocket.send(result.c_str(), result.size() + 1, address, port);
}