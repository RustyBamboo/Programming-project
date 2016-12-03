#include "button.hpp"

namespace gui {
Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string t) {
    shape.setPosition(pos);
    shape.setSize(size);

    text.setPosition(pos);
    text.setColor(sf::Color::White);
    if (!font.loadFromFile("resources/Raleway-Light.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
    }
    text.setFont(font);
    text.setString(t);

    clicked = false;
}

bool Button::checkPoint(int x, int y) {
    if (x > shape.getPosition().x && x <= shape.getPosition().x + shape.getSize().x
            && y > shape.getPosition().y && y <= shape.getPosition().y + shape.getSize().y)
        return true;
    return false;
}

void Button::draw(sf::RenderWindow &window) {
    // window.draw(shape);
    window.draw(text);
}
void Button::update(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (checkPoint(event.mouseButton.x, event.mouseButton.y)) {
                clicked = true;

            }

        }
    }
}
}