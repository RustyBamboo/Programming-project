#include "form.hpp"
namespace gui {
Form::Form() {}
void Form::draw(sf::RenderWindow &window) {
    for (auto &box : textboxes) {
        box->draw(window);
    }
    button->draw(window);
}
bool Form::update(sf::Event &event) {
    for ( auto &box : textboxes) {
        box->update(event);
    }
    button->update(event);
    if (button->clicked) return true;
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Return)
        {
            return true;
        }
    }
    return false;
}
void Form::addTextBox(gui::TextBox & textbox) {
    textboxes.push_back(&textbox);
}
void Form::setButton(gui::Button & b) {
    button = &b;
}
std::vector<std::string> Form::process() {
    std::vector<std::string> hold;
    for ( auto &box : textboxes) {
        hold.push_back(box->getString());
        box->clear();
    }
    button->clicked = false;
    return hold;
}
}