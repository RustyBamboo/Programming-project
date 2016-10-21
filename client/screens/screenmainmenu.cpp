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
    sf::Event event;
    bool running = true;

    while (running)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (form.update(event)) { //If button was clicked...
                std::vector<std::string> allTheFields = form.process();

                if (allTheFields[0].size() > 0 && allTheFields[1].size() > 0 && allTheFields[1].size() <= 12) {
                    ScreenGame::setServerIP(sf::IpAddress(allTheFields[0]));
                    ScreenGame::setName(allTheFields[1]);
                    std::cout << "Inputed: " << allTheFields[0] << " " << allTheFields[1] << std::endl;
                    return (1);
                }
                else {
                    textBoxAddr.setText(allTheFields[0]);
                    textBoxName.setText(allTheFields[1]);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    return (-1);
                }
            }
        }

        window.clear();
        form.draw(window);
        window.display();
    }

    return (-1);
}
