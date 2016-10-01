#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H


class ScreenGame : public CScreen
{
private:
	sf::RectangleShape rect; //As an example
public:
    ScreenGame();
    virtual int run(sf::RenderWindow &window);
};

#endif