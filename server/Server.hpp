#pragma once
#include "../common/include.hpp"
#include <stdexcept>
#include <stack>

class Server
{
private:
    const unsigned short TCP_PORT = 5001;
    const int TICK_TIME_MILLIS = 20;
    sf::TcpListener newPlayersListener;
    TickPacket tickPacket;
    sf::Packet updates_packet;
    std::map< std::unique_ptr<sf::TcpSocket> , WorldMap::ID_TYPE> players;

    std::stack<sf::Color> colors;
    sf::Color getColor();
    void addColor(sf::Color c);
    void addColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue);

    uint32_t tick_number;
    WorldMap worldMap;
    void connectPlayer();
    void updateNewPlayer(sf::TcpSocket& socket, WorldMap::ID_TYPE id);
    void tick();
public:
    Server();
    ~Server();
    void run();
};
