#include "textbox.hpp"

namespace gui {
TextBox::TextBox(sf::Vector2f pos, sf::Vector2f size, int max) : cursor(sf::Vector2f(5,size.y-10)) {
    box.setPosition(pos);
    box.setSize(size);
    cursor.setPosition(sf::Vector2f(pos.x, pos.y+5));
    text.setPosition(pos);
    text.setColor(sf::Color::Black);
    if (!font.loadFromFile("resources/verdanab.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
    }
    text.setFont(font);
    maxlength = max;

}
void TextBox::addText(sf::String &s) {
    sf::String string = text.getString();
    text.setString(string + s);
    cursor.setPosition(text.getLocalBounds().width + box.getPosition().x);
}
void TextBox::removeLast() {
    text.setString(text.getString().substring(0, text.getString().getSize()-1));
    cursor.setPosition(text.getLocalBounds().width + box.getPosition().x);
}
void TextBox::draw(sf::RenderWindow &window) {
    window.draw(box);
    cursor.draw(window);
    window.draw(text);
}
void TextBox::update(sf::Event &event) {

    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) {
                removeLast();
            }
            else if (text.getString().getSize() < maxlength){
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