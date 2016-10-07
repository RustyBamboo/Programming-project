/*

  Main function. Loads up the different screens and manages them. 
  This is also where sf::RenderWindow is defined.

*/

#include "include.hpp"
#include "screens/screens.hpp"
#include <SFML/Network.hpp>


const unsigned short PORT = 5001;
const std::string IPADDRESS("192.168.1.149");
int main() {
  std::cout<<"Works?"<<std::endl;
  sf::TcpSocket socket;
  if(socket.connect(IPADDRESS, PORT) == sf::Socket::Done) {
    std::cout<<"connected"<<std::endl;
  }
  else {
    std::cout<<"rip"<<std::endl;
  }
  srand(time(NULL)); //Pick a seed
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
