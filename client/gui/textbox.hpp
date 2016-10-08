#ifndef GUI_TEXTBOX_HPP
#define GUI_TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "cursor.hpp"
namespace gui {
    class TextBox {
    private:
        sf::RectangleShape box;
        bool isSelected;
        sf::Text text;
        sf::Font font;
        int maxlength;

        gui::Cursor cursor;

        void addText(sf::String &s);
        void removeLast();
    public:
        TextBox(sf::Vector2f pos, sf::Vector2f size, int max);
        void draw(sf::RenderWindow &window);
        void update(sf::Event &event);
        void clear();
        std::string getString();

    };
}

#endif