#include "screengame.hpp"

ScreenGame::ScreenGame() {
    thread = new sf::Thread(&ScreenGame::getUDP, this);

    udpSocket.bind(UDPPORT);

}

void ScreenGame::removeSpaces(std::string &str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

//Process incoming UDP and then either moves an entity or creates a new one
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
    std::string s;
    std::cout << "enter username: ";
    std::cin >> s;
    sf::Packet packet;
    packet << s;

    //Establish a connection with the server
    sf::TcpSocket socket;
    if (socket.connect(IPADDRESS, TCPPORT) == sf::Socket::Done) {
        socket.send(packet);
        sf::Packet b;
        socket.receive(b); //Get the ID from the server
        int msg;
        if (b >> msg) {
            std::cout << "id is: " << msg << std::endl;
            worldMap.addPlayer(msg);
            thread->launch();
            std::cout << "launched" << std::endl;
        }
    }
    else {
        return (-1); //Server ain't up. So close client.
    }



    float dt;
    sf::Event Event;
    bool running = true;




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
        worldMap.sendInfo(udpSocket, IPADDRESS, UDPSENDTOPORT);
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
