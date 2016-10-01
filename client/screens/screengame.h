#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H


#include "cscreen.h"

#include <SFML/Graphics.hpp>

class ScreenGame : public CScreen
{
private:
	sf::RectangleShape rect; //As an example
public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif