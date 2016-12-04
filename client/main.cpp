/*

  Main function. Loads up the different screens and manages them.
  This is also where sf::RenderWindow is defined.

*/

#include "include.hpp"
#include "screens/screens.hpp"
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "gui/sound.hpp"
#include "gui/font.hpp"
#include <memory>


int main() {
    srand(time(NULL)); //Pick a seed

    std::cout << sf::IpAddress::getPublicAddress();

    gui::Sound::init(); //Load all sound buffers
    gui::Font::init();  //Load the font buffer

    sf::RenderWindow window(sf::VideoMode(WorldMap::width, WorldMap::height), "Galaxy Blasters"); //Loads window

    //Load background and mainmenu music
    sf::Music music;
    if (!music.openFromFile("resources/song.wav"))
        return -1; // error
    music.setLoop(true);
    music.setVolume(25);


    sf::Music gamemusic;
    if (!gamemusic.openFromFile("resources/gamesong.wav"))
        return -1; // error
    gamemusic.setLoop(true);
    gamemusic.setVolume(25);
    // gamemusic.play();

    //The screen class returns an int, which tells which Screen (mainmenu, game) to run
    std::unique_ptr<CScreen> cur_screen;
    //Screen state manager
    music.play();
    cur_screen.reset(new ScreenMainMenu());
    while (true)
        switch (cur_screen->run(window))
        {
        case 1:
            music.stop();
            gamemusic.play();
            cur_screen.reset(new ScreenGame());
            break;
        case 2:
            gamemusic.stop();
            music.play();
            cur_screen.reset(new ScreenMainMenu());
            break;
        default:
            return 0;
        };
    return 0;
}
