#include "screengame.h"

ScreenGame::ScreenGame() {
    //Remove this rect stuff
 std::cout<<"Game was made!"<<std::endl;
    ent.reset(new Player());
}

int ScreenGame::run(sf::RenderWindow &window) {
    float dt;
    sf::Event Event;
    bool running = true;

    while (running) {
        // Verifying events
        while (window.pollEvent(Event)) {
            // Window closed
            if (Event.type == sf::Event::Closed) {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed) {
                switch (Event.key.code) {
                case sf::Keyboard::Escape:
                    return (0);
                }
            }
        }

        window.clear(sf::Color(0, 0, 0, 0));
        ent->draw(window);
        window.display();
    }

    return -1;
}
