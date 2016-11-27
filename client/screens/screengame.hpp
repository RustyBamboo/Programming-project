/*
    Class to manage the actual game.
*/

#ifndef SCREEN_GAME_HPP
#define SCREEN_GAME_HPP

#include "cscreen.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <stdexcept>

#include "../../common/include.hpp"

class ScreenGame : public CScreen
{
private:
    unsigned short TCP_PORT = 5001;
    static sf::IpAddress SERVER_IP;
    static std::string playerName;
    sf::TcpSocket serverConnection;
    uint32_t last_packet;
    WorldMap worldMap;
    WorldMap::ID_TYPE player_id;
    bool created;
    void doTick();
    void doHandshake();
    void handleUserInput();
public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
    static void setServerIP (const sf::IpAddress &address);
    static void setName (const std::string &_name);
};

#endif
