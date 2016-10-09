#pragma once
#include "../common/include.hpp"
class Server 
{
private:
    const unsigned short TCP_PORT = 5001;
    const int TICK_TIME_MILLIS = 100;
		sf::TcpListener newPlayersListener;
		sf::Mutex tick_mutex;
		TickPacket tickPacket;
		sf::Packet updates_packet;
		uint32_t tick_number;
		std::map< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE> players;
    WorldMap worldMap;
    void connectPlayers();
    void tick();
public:
    Server();
    void run();
};
