/*
    Class to manage the actual game.
*/

#ifndef SCREEN_GAME_HPP
#define SCREEN_GAME_HPP

#include "cscreen.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>

#include "../../common/include.hpp"

class ScreenGame : public CScreen
{
private:
    unsigned short TCP_PORT = 5001;
    unsigned short UDP_PORT = 5003;
    std::string IP_ADDRESS= "24.250.152.209";

    sf::UdpSocket udpSocket;
		uint32_t last_packet;
    WorldMap worldMap;

		void doTick();
		void doHandshake();
public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif
