#pragma once

#include <SFML/Graphics.hpp>

namespace gui {
    class Font {
    public:
        static sf::Font font;
        static void init();
    };
}