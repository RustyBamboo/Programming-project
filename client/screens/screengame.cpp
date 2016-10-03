#include "screengame.h"

ScreenGame::ScreenGame() {
    //Remove this rect stuff
 std::cout<<"Game was made!"<<std::endl;
    ray.reset(new Bullet(sf::Vector2f(50,100), sf::Vector2f(0, 0.01)));
    mob.reset(new Mob(50, 7, sf::Vector2f(50,50), sf::Vector2f(0.01, 0.01)));
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

        ray->tick();
        ray->draw(window);

        mob->tick();
        mob->draw(window);

        worldMap.tick();
        worldMap.draw(window);
        window.display();
    }

    return -1;
}
