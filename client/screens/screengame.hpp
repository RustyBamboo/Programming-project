/*
    Class to manage the actual game.
*/

#ifndef SCREEN_GAME_HPP
#define SCREEN_GAME_HPP

#include "cscreen.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>

#include "screengame.hpp"

#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../entities/bullet.hpp"
#include "../entities/mob.hpp"

#include "../worldmap/worldmap.hpp"

class ScreenGame : public CScreen
{
private:
    const unsigned short TCPPORT = 5001; //Client's port for TCP
    const unsigned short UDPPORT = 5003; //Client's port for UDP
    const unsigned short UDPSENDTOPORT = 5002; //Which port server is for UDP
    const std::string IPADDRESS= "24.250.152.209"; //Server IPAddress

    sf::Thread *thread;
    sf::UdpSocket udpSocket;

    WorldMap worldMap;

    void getUDP();

    void removeSpaces(std::string &str);

public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif