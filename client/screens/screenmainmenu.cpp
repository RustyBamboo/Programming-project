#include "screenmainmenu.hpp"


ScreenMainMenu::ScreenMainMenu() : textBoxAddr(sf::Vector2f(10, 10), sf::Vector2f(300, 50), 25),
    textBoxName(sf::Vector2f(10, 70), sf::Vector2f(300, 50), 12),
    buttonSubmit(sf::Vector2f(10, 140), sf::Vector2f(200, 50), "Submit")
{
    form.addTextBox(textBoxAddr);
    form.addTextBox(textBoxName);
    form.setButton(buttonSubmit);
    playing = false;
}

/*

    This is the mainmenu,
    This is also the pause menu

*/
int ScreenMainMenu::run(sf::RenderWindow &window)
{
    window.setView(window.getDefaultView());
    sf::Event Event;
    bool Running = true;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;


    if (!Font.loadFromFile("resources/verdanab.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Play");
    Menu1.setPosition(280.f, 160.f);

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Exit");
    Menu2.setPosition(280.f, 220.f);

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Continue");
    Menu3.setPosition(280.f, 160.f);


    while (Running)
    {
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (form.update(Event)) { //If button was clicked...
                std::vector<std::string> allTheFields = form.process();

                ScreenGame::setServerIP(sf::IpAddress(allTheFields[0]));
                ScreenGame::setName(allTheFields[1]);
                std::cout<<allTheFields[0]<<" "<<allTheFields[1]<<std::endl;

            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                case sf::Keyboard::Up:
                    menu = 0;
                    break;
                case sf::Keyboard::Down:
                    menu = 1;
                    break;
                case sf::Keyboard::Return:
                    if (menu == 0)
                    {
                        //Let's get play !

                        playing = true;
                        return (1);
                    }
                    else
                    {
                        //Let's get work...
                        return (-1);
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (menu == 0)
        {
            Menu1.setColor(sf::Color(255, 0, 0, 255));
            Menu2.setColor(sf::Color(255, 255, 255, 255));
            Menu3.setColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            Menu1.setColor(sf::Color(255, 255, 255, 255));
            Menu2.setColor(sf::Color(255, 0, 0, 255));
            Menu3.setColor(sf::Color(255, 255, 255, 255));
        }

        window.clear();

        if (playing)
        {
            window.draw(Menu3);
        }
        else
        {
            window.draw(Menu1);
        }
        window.draw(Menu2);
        form.draw(window);
        window.display();
    }

    return (-1);
}
