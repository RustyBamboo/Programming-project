#include <SFML/Network.hpp>
#include <iostream>

class Server {
private:
	const unsigned short PORT = 5001;
	bool running;
	sf::TcpSocket socket;
	sf::Thread* threadCP;
	void connectPlayers() {
		sf::TcpListener listener;
		listener.listen(PORT);

		while (running) {
			listener.accept(socket);
			std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
			sf::Packet packet;
			socket.receive(packet);

			sf::Uint32 x;
			std::string s;
			double d;
			if (packet >> x >> s >> d)
			{
				std::cout << x << " " << s << " " << d << std::endl;
			}
			
			sf::Packet sPacket;
			sPacket << x + 1000;
			socket.send(sPacket);
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