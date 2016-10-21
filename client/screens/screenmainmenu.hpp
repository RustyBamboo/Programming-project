/* 
	Load menu and pause menu screen class.
	Someone can work on this.
*/

#ifndef SCREEN_MAIN_MENU_HPP
#define SCREEN_MAIN_MENU_HPP

#include <iostream>
#include "cscreen.hpp"

#include "../gui/textbox.hpp"
#include "../gui/button.hpp"
#include "../gui/form.hpp"
#include "screengame.hpp"


class ScreenMainMenu : public CScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
    gui::TextBox textBoxAddr;
    gui::TextBox textBoxName;
    gui::Button buttonSubmit;
    gui::Form form;
public:
    ScreenMainMenu();
    virtual int run(sf::RenderWindow &window);
};

#endif