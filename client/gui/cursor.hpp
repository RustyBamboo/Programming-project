#ifndef GUI_CURSOR_HPP
#define GUI_CURSOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

namespace gui {
    class Cursor {
    private:
        sf::RectangleShape shape;
        int blinkrate;
        sf::Clock clock;
        bool isOn;
    public:
        Cursor(sf::Vector2f size);
        void setPosition(sf::Vector2f pos);
        void setPosition(float x);
        void shiftPosition(float x);
        void draw(sf::RenderWindow &window);
    };
}

#endif