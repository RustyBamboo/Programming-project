#include <SFML/Network.hpp>
#include <iostream>

const unsigned short PORT = 5001;
int main() {
	sf::TcpSocket socket;

	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(socket);
	std::cout<<"New client connected: "<<socket.getRemoteAddress()<<std::endl;

	return 0;

}