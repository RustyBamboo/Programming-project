#include "textbox.hpp"

namespace gui {
TextBox::TextBox(sf::Vector2f pos, sf::Vector2f size, int max) : cursor(sf::Vector2f(5, size.y - 10)) {
    shape.setPosition(pos);
    shape.setSize(size);
    cursor.setPosition(sf::Vector2f(pos.x, pos.y + 5));
    text.setPosition(pos);
    text.setColor(sf::Color::Black);
    if (!font.loadFromFile("resources/verdanab.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
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
    cursor.setPosition(text.getLocalBounds().width + shape.getPosition().x);
}
void TextBox::removeLast() {
    if (text.getString().getSize() == 0) return;
    sf::String old = text.getString();
    old.erase(old.getSize ()-1,1);
    text.setString(old);
    cursor.setPosition(text.getLocalBounds().width + shape.getPosition().x);
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
            }
            else {
                selected = false;
                cursor.hideCursor();
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

void TextBox::clear() {
    text.setString("");
}

std::string TextBox::getString() {
    return std::string(text.getString());
}

}
