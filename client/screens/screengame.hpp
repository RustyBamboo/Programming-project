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
    const unsigned short PORT = 5001;
    const std::string IPADDRESS= "192.168.1.149";

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