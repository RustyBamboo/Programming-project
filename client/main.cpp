#include "include.hpp"
#include "screens/screens.h"

int main() {
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
