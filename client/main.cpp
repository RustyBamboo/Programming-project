/*

  Main function. Loads up the different screens and manages them.
  This is also where sf::RenderWindow is defined.

*/

#include "include.hpp"
#include "screens/screens.hpp"
#include <SFML/Network.hpp>


void updateGame() {
  sf::UdpSocket socket;
  socket.bind(55002);
  while(true) {
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(buffer, sizeof(buffer), received, sender, port);
    std::cout << sender.toString() << " said: " << buffer << std::endl;
  }
}

const unsigned short PORT = 5001;
const std::string IPADDRESS("192.168.1.149");
int main() {
  srand(time(NULL)); //Pick a seed


sf::Thread *threadCP;
threadCP = new sf::Thread(&updateGame);
        threadCP->launch();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  std::string s;
  std::cout<<"enter username: ";
  std::cin>>s;
// Group the variables to send into a packet
  sf::Packet packet;
  packet <<s;

  sf::TcpSocket socket;
  if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done) {
    socket.send(packet);
    sf::Packet b;
    socket.receive(b);
    std::string msg;
    if(b >> msg)
      std::cout<<msg<<std::endl;
  }
  else {
    std::cout << "rip" << std::endl;
  }


 if (threadCP)
        {
            threadCP->wait();
            delete threadCP;
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////







  std::vector<CScreen *> screens;
  int screen = 0;
  sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

  ScreenMainMenu s0;
  screens.push_back(&s0);

  ScreenGame s1;
  screens.push_back(&s1);

  //The screen class returns an int, which tells which Screen (mainmenu, game) to run
  while (screen >= 0) {
    screen = screens[screen]->run(window);
  }

  return 0;
}
