#include <SFML/Network.hpp>
#include <iostream>
#include "worldmap.hpp"
#include "player.hpp"

//The IDs of players may as well be their usernames
class Server {
private:
    const unsigned short TCPPORT = 5001; //Server is looking for TCP in this port
    const unsigned short UDPPORT = 5002; //Server is looking for UDP in this port
    bool running;
    sf::TcpSocket socket;
    sf::UdpSocket udpSocket;

    sf::Thread* threadCP;
    sf::Thread* threadUpdate;

    WorldMap worldMap;
    void connectPlayers() {
        sf::TcpListener listener;

        //This got around some error of failing to bind to the port. (I assume from improper closing)
        if (listener.listen(TCPPORT) == sf::TcpListener::Error) {
            listener.close();
            listener.listen(TCPPORT);
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

    void removeSpaces(std::string &str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}
    void update() {
        sf::Clock clock;
        sf::Time elapsed = clock.getElapsedTime();
        while (running) {
            elapsed = clock.getElapsedTime();
            if (elapsed.asMilliseconds() >= 100) {
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
            std::string id(buffer, 0, 6);
            std::string xpos(buffer, 6, 9);
            std::string ypos(buffer, 15, 9);
            removeSpaces(id);
            removeSpaces(xpos);
            removeSpaces(ypos);
            worldMap.update(stoi(id), stoi(xpos), stoi(ypos));
        }
    }

public:
    Server() : running(true) {
        udpSocket.bind(UDPPORT);

        threadCP = new sf::Thread(&Server::connectPlayers, this);
        threadCP->launch(); //Let players join and connect to the server


        threadUpdate = new sf::Thread(&Server::update, this);
        threadUpdate->launch(); //Sends out all positions to clients

        receive(); //Let server read incoming UDP packets, and update entities positions


        if (threadCP) {
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