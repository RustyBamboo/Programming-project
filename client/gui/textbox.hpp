#ifndef GUI_TEXTBOX_HPP
#define GUI_TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "cursor.hpp"
namespace gui {
class TextBox {
private:
    sf::RectangleShape shape;
    bool isSelected;
    sf::Text text;
    sf::Font font;
    unsigned int maxlength;

    bool selected;

    bool checkPoint(int x, int y);

    gui::Cursor cursor;

    void addText(sf::String &s);
    void removeLast();
public:
    TextBox(sf::Vector2f pos, sf::Vector2f size, int max);
    void draw(sf::RenderWindow &window);
    void update(sf::Event &event);
    void clear();
    void setText(std::string &str);
    std::string getString();
    void noSelect();

};
}

#endif
