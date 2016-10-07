#include "screengame.hpp"

ScreenGame::ScreenGame() {
    //Remove this rect stuff
    std::cout << "Game was made!" << std::endl;

    thread = new sf::Thread(&ScreenGame::getUDP, this);

    udpSocket.bind(55002);

}

void ScreenGame::removeSpaces(std::string &str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}
void ScreenGame::getUDP() {
    while (true) {
        char buffer[36];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
        std::string name(buffer, 0, 12);
        std::string id(buffer, 12, 6);
        std::string xpos(buffer, 18, 9);
        std::string ypos(buffer, 27, 9);
        removeSpaces(name);
        removeSpaces(id);
        removeSpaces(xpos);
        removeSpaces(ypos);
        std::cout << "Name: " << name << " id " << id << " x: " << xpos << " y: " << ypos << std::endl;
        worldMap.processEntity(stoi(id), stoi(xpos), stoi(ypos));
    }
}

int ScreenGame::run(sf::RenderWindow &window) {
    float dt;
    sf::Event Event;
    bool running = true;


    thread->launch();
    std::cout << "launched?" << std::endl;

    while (running) {
        while (window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed) {
                switch (Event.key.code) {
                case sf::Keyboard::Escape:
                    return (0); //Goes to Pause Menu
                }
            }
        }

        window.clear(sf::Color(0, 0, 0, 0));

        worldMap.tick();
        worldMap.draw(window);

        window.display();
    }
    if (thread)
    {
        thread->wait();
        delete thread;
    }
    return -1;
}
