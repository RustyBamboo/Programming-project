#pragma once

#include "../../common/include.hpp"
#include <SFML/Audio.hpp>
namespace gui {
class Sound {
private:
    static sf::SoundBuffer bufferHit;
    static sf::SoundBuffer bufferLevelUp;
    static sf::SoundBuffer bufferShoot;
    static sf::Sound sound;
public:
    static void init();
    static void playHit();
    static void playLevelUp();
    static void playShoot();
};
}