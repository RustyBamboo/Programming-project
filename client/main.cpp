/*

  Main function. Loads up the different screens and manages them.
  This is also where sf::RenderWindow is defined.

*/

#include "include.hpp"
#include "screens/screens.hpp"
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "gui/sound.hpp"
#include <memory>


int main() {
  srand(time(NULL)); //Pick a seed

  std::cout << sf::IpAddress::getPublicAddress();

  gui::Sound::init();

  sf::RenderWindow window(sf::VideoMode(WorldMap::width, WorldMap::height), "Game");

  sf::Music music;
  if (!music.openFromFile("resources/song.wav"))
    return -1; // error
  music.setLoop(true);
  music.setVolume(25);
  music.play();

  //The screen class returns an int, which tells which Screen (mainmenu, game) to run
  std::unique_ptr<CScreen> cur_screen;
  cur_screen.reset(new ScreenMainMenu());
  while(true)
    switch(cur_screen->run(window))
    {
      case 1:
        cur_screen.reset(new ScreenGame());
        break;
      case 2:
        cur_screen.reset(new ScreenMainMenu());
        break;
      default:
        return 0;
    };
  return 0;
}
