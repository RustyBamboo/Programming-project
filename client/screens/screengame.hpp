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
    sf::IpAddress SERVER_IP;

    sf::UdpSocket udpSocket;
		uint32_t last_packet;
    WorldMap worldMap;
		WorldMap::ID_TYPE player_id;
		void doTick();
		void doHandshake();
		void handleUserInput();
public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif
