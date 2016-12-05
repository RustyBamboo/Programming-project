#include "cursor.hpp"

namespace gui {
//setting up the cursor
Cursor::Cursor(sf::Vector2f size) {
    shape.setSize(size);
    blinkrate = 1000;
    shape.setFillColor(sf::Color::White);
    isOn = true;
    show = false;
}

void Cursor::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
}
void Cursor::setPosition(float pos) {
    shape.setPosition(sf::Vector2f(pos, shape.getPosition().y));
}
void Cursor::shiftPosition(float x) {
    shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y));
}
void Cursor::draw(sf::RenderWindow &window) {
    if (show) {
        if (isOn == false && clock.getElapsedTime().asMilliseconds() >= blinkrate) {
            isOn = true;
            clock.restart();
        }
        else if (isOn == true && clock.getElapsedTime().asMilliseconds() >= blinkrate) {
            isOn = false;
            clock.restart();
        }
        if (isOn)
            window.draw(shape);
    }
}
//show and hide methods
void Cursor::showCursor() {
    show = true;
}
void Cursor::hideCursor() {
    show = false;
}
}