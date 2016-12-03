#include "font.hpp"

namespace gui {
    sf::Font Font::font;
    void Font::init() {
        font.loadFromFile("resources/Raleway-Light.ttf");
    }
}