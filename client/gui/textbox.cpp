#include "textbox.hpp"

namespace gui {
TextBox::TextBox(sf::Vector2f pos, sf::Vector2f size, int max) : cursor(sf::Vector2f(2, size.y - 10)) {
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(sf::Color(0,0,0,0));
    shape.setOutlineThickness(2);
    cursor.setPosition(sf::Vector2f(pos.x, pos.y + 5));
    text.setPosition(sf::Vector2f(pos.x+5, pos.y));
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    if (!font.loadFromFile("resources/Raleway-Light.ttf"))
    {
        std::cerr << "Error loading Raleway-Light.ttf" << std::endl;
    }
    text.setFont(font);
    maxlength = max;

    selected = false;
}
bool TextBox::checkPoint(int x, int y) {
    if (x > shape.getPosition().x && x <= shape.getPosition().x + shape.getSize().x
            && y > shape.getPosition().y && y <= shape.getPosition().y + shape.getSize().y)
        return true;
    return false;
}
void TextBox::addText(sf::String &s) {
    sf::String string = text.getString();
    text.setString(string + s);
    cursor.setPosition(text.getLocalBounds().width + shape.getPosition().x + 6);
}
void TextBox::removeLast() {
    if (text.getString().getSize() == 0) return;
    sf::String old = text.getString();
    old.erase(old.getSize () - 1, 1);
    text.setString(old);
    cursor.setPosition(text.getLocalBounds().width + shape.getPosition().x + 6);
}
void TextBox::draw(sf::RenderWindow &window) {
    window.draw(shape);
    cursor.draw(window);
    window.draw(text);
}
void TextBox::update(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (checkPoint(event.mouseButton.x, event.mouseButton.y)) {
                selected = true;
                cursor.showCursor();
                shape.setOutlineColor(sf::Color(203,65,11));
            }
            else {
                selected = false;
                cursor.hideCursor();
                shape.setOutlineColor(sf::Color::White);
            }

        }
    }
    if (event.type == sf::Event::TextEntered) {
        if (selected && event.text.unicode < 128) {
            if (event.text.unicode == 8) {
                removeLast();
            }
            else if (text.getString().getSize() < maxlength) {
                sf::String test = event.text.unicode;
                addText(test);
            }

        }
    }


}

void TextBox::setText(std::string &str) {
    text.setString(str);
}
void TextBox::clear() {
    text.setString("");
}

std::string TextBox::getString() {
    return std::string(text.getString());
}

void TextBox::noSelect() {
    selected = false;
    cursor.hideCursor();
    shape.setOutlineColor(sf::Color::White);
}

}
