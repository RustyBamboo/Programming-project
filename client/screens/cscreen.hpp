#ifndef CSCREEN_HPP
#define CSCREEN_HPP

#include <SFML/Graphics.hpp>

class CScreen
{
public :
    virtual int run (sf::RenderWindow &window) = 0;
    virtual ~CScreen(){};
};

#endif
