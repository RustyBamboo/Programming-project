#include <SFML/Network.hpp>
#include <iostream>


//The ID's of players may as well be their usernames
class Server {
private:
	const unsigned short PORT = 5001;
	bool running;
	sf::TcpSocket socket;
	sf::Thread* threadCP;
	std::vector<std::string> usernames;
	void connectPlayers() {
		sf::TcpListener listener;
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
				usernames.push_back(s);
				std::cout << "-----------Current connected players-------------"<<std::endl;
				for (std::vector<std::string>::const_iterator i = usernames.begin(); i != usernames.end(); ++i)
					std::cout << "\t" << *i << std::endl;
				sf::Packet sPacket;
				sPacket << std::string("Welcome " + s);
				socket.send(sPacket);
			}
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