/* 
	Load menu and pause menu screen class.
	Someone can work on this.
*/

#ifndef SCREEN_MAIN_MENU_HPP
#define SCREEN_MAIN_MENU_HPP

#include <iostream>
#include "cscreen.hpp"

#include <SFML/Graphics.hpp>

#include "../gui/textbox.hpp"
#include "../gui/button.hpp"
#include "../gui/form.hpp"

class ScreenMainMenu : public CScreen
{
private:
    bool playing;
    gui::TextBox inputTest;
    gui::Form form;
    gui::Button button;
public:
    ScreenMainMenu();
    virtual int run(sf::RenderWindow &window);
};

#endif