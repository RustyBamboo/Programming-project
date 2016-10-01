#ifndef SCREEN_MAIN_MENU_H
#define SCREEN_MAIN_MENU_H


class ScreenMainMenu : public CScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
public:
    ScreenMainMenu();
    virtual int run(sf::RenderWindow &window);
};

#endif