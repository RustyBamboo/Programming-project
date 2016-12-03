#pragma once

#include "../../common/include.hpp"
#include <SFML/Audio.hpp>
namespace gui {
class Sound {
private:
    static sf::SoundBuffer bufferHit;
    static sf::SoundBuffer bufferLevelUp;
    static sf::SoundBuffer bufferShoot;
    static sf::SoundBuffer bufferMenuSelect;
    static sf::Sound sound;
public:
    static sf::Music musicDeath;
    static void init();
    static void playHit();
    static void playLevelUp();
    static void playShoot();
    static void playDeath();
    static void playMenuSelect();
};
}