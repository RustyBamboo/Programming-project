#ifndef CSCREEN_H
#define CSCREEN_H

#include <SFML/Graphics.hpp>

class CScreen
{
public :
    virtual int run (sf::RenderWindow &window) = 0;
};

#endif
