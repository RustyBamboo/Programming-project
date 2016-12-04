#pragma once

#include <SFML/Graphics.hpp>

//Loads a font into memory buffer
namespace gui {
    class Font {
    public:
        static sf::Font font;
        static void init();
    };
}