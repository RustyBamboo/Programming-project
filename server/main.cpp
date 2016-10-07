#include <SFML/Network.hpp>
#include <iostream>
#include "worldmap.hpp"
#include "player.hpp"

//The IDs of players may as well be their usernames
class Server {
private:
    const unsigned short PORT = 5001;
    const unsigned short UDPPORT = 5002;
    bool running;
    sf::TcpSocket socket;
    sf::UdpSocket udpSocket;

    sf::Thread* threadCP;
    sf::Thread* threadUpdate;

    WorldMap worldMap;
    void connectPlayers() {
        sf::TcpListener listener;

        //This got around some error of failing to bind to the port. (I assume from improper closing)
        if (listener.listen(PORT) == sf::TcpListener::Error) {
            listener.close();
            listener.listen(PORT);
        }

        while (running) {
            listener.accept(socket);
            sf::Packet packet;
            socket.receive(packet);

            std::string s;
            if (packet >> s)
            {
                std::cout << s << " connected: " << socket.getRemoteAddress() << std::endl;
                int id = rand() % 10000;

                worldMap.genEntity(id, s, socket.getRemoteAddress());

                sf::Packet sPacket;
                sPacket << id;
                socket.send(sPacket);
            }
        }
    }

    void update() {
        sf::Clock clock;
        sf::Time elapsed = clock.getElapsedTime();
        while (running) {
            elapsed = clock.getElapsedTime();
            if (elapsed.asSeconds() >= 1) {
                worldMap.update(udpSocket);
                elapsed = clock.restart();
            }

        }
    }

    void receive() {
        while (running) {
            char buffer[36];
            std::size_t received = 0;
            sf::IpAddress sender;
            unsigned short port;
            udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
            std::cout<<"I got " << buffer<<std::endl;
        }
    }

public:
    Server() : running(true) {
        udpSocket.bind(UDPPORT);

        threadCP = new sf::Thread(&Server::connectPlayers, this);
        threadCP->launch();


        threadUpdate = new sf::Thread(&Server::update, this);
        threadUpdate->launch();

        receive();
        if (threadCP)
        {
            threadCP->wait();
            delete threadCP;
        }
        if (threadUpdate) {
            threadUpdate->wait();
            delete threadUpdate;
        }
    }

};
int main() {
    Server server;
    return 0;

}