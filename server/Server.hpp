#pragma once
#include "../common/include.hpp"
#include <stdexcept>

class Server 
{
private:
    const unsigned short TCP_PORT = 5001;
    const int TICK_TIME_MILLIS = 20;
		sf::TcpListener newPlayersListener;
		TickPacket tickPacket;
		sf::Packet updates_packet;
    std::map< std::unique_ptr<sf::TcpSocket> ,WorldMap::ID_TYPE> players;
		uint32_t tick_number;
    WorldMap worldMap;
    void connectPlayer();
    void tick();
public:
    Server();
    ~Server();
    void run();
};
