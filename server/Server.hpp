#pragma once
#include "../common/include.hpp"
#include <mutex>
class Server 
{
private:
    const unsigned short TCP_PORT = 5001;
    const unsigned short UDP_PORT = 5002;
    const int TICK_TIME_MILLIS = 100;
		sf::TcpListener newPlayersListener;
    sf::UdpSocket tickSocket;

    WorldMap worldMap;
    void connectPlayers();
    void tick();
public:
    Server();
    void run();
};
