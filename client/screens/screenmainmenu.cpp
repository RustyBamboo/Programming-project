#include "screenmainmenu.hpp"


ScreenMainMenu::ScreenMainMenu() : textBoxAddr(sf::Vector2f(115, 700), sf::Vector2f(300, 45), 25),
    buttonSubmit(sf::Vector2f(115, 750), sf::Vector2f(100, 50), "Submit")
{
    form.addTextBox(textBoxAddr);
    form.setButton(buttonSubmit);
    playing = false;
    font.loadFromFile("resources/Raleway-Light.ttf");
    exitText.setString("exit");
    exitText.setFont(font);
    exitText.setCharacterSize(30);
    exitText.setPosition(sf::Vector2f(115,800));

    backgroundTexture.loadFromFile("resources/mainmenu.png");
    backgroundSprite.setTexture(backgroundTexture);

    boundingRect.setSize(sf::Vector2f(100, 50));
    boundingRect.setFillColor(sf::Color(0,0,0,0));
    boundingRect.setOutlineColor(sf::Color::White);
    boundingRect.setOutlineThickness(1);
}

/*

    This is the mainmenu,
    This is also the pause menu

*/
int ScreenMainMenu::run(sf::RenderWindow &window)
{
    std::vector<std::string> allTheFields;
    allTheFields.push_back("127.0.0.1");
    textBoxAddr.setText(allTheFields.at(0));
    window.setView(window.getDefaultView());
    sf::Event event;
    bool running = true;

    int optionPressed = 0;
    while (running)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    optionPressed = 1;
                    form.noSelect();
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    optionPressed = 0;
                }
                if (optionPressed == 1 && event.key.code == sf::Keyboard::Return)
                {
                    return -1;
                }
            }
            if (optionPressed == 0 && form.update(event)) { //If button was clicked...
                allTheFields = form.process();
                if (allTheFields[0].size() > 0 && allTheFields[1].size() > 0) {
                    ScreenGame::setServerIP(sf::IpAddress(allTheFields[0]));
                    std::cout << "Inputted: " << allTheFields[0] << std::endl;
                    return (1);
                }
                else {
                    textBoxAddr.setText(allTheFields[0]);
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        form.draw(window);
        window.draw(exitText);
        if(optionPressed == 0) {
            boundingRect.setPosition(113, 748);
        }
        if(optionPressed == 1) {
            boundingRect.setPosition(113, 798);
        }
        window.draw(boundingRect);
        window.display();
    }

    return (-1);
}
