#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "font.hpp"

//Button class the checks if user clicks on it
namespace gui {
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
public:
    bool clicked;
    Button(sf::Vector2f pos, sf::Vector2f size, std::string text);
    bool checkPoint(int x, int y);
    void draw(sf::RenderWindow &window);
    void update(sf::Event &event);
};
}

#endif