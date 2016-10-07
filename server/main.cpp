#include <SFML/Network.hpp>
#include <iostream>

const unsigned short PORT = 5001;
class Server {
private:
	bool running;
	sf::TcpSocket socket;
	sf::Thread* threadCP;
	void connectPlayers() {
		sf::TcpListener listener;
		listener.listen(PORT);

		while (running) {
			listener.accept(socket);
			std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
		}
	}

public:
	Server() : running(true) {
		threadCP = new sf::Thread(&Server::connectPlayers, this);
		threadCP->launch();
		if (threadCP)
		{
			threadCP->wait();
			delete threadCP;
		}
	}

};
int main() {
	Server server;
	return 0;

}