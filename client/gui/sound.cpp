#include "sound.hpp"
namespace gui {
sf::SoundBuffer Sound::bufferHit;
sf::SoundBuffer Sound::bufferLevelUp;
sf::SoundBuffer Sound::bufferShoot;
sf::Music Sound::musicDeath;


sf::Sound Sound::sound;

void Sound::init() {
    if (!bufferHit.loadFromFile("resources/hit.wav"))
        throw std::runtime_error("No hit.wav");
    if (!bufferLevelUp.loadFromFile("resources/levelup.wav"))
        throw std::runtime_error("No levelup.wav");
    if (!bufferShoot.loadFromFile("resources/shoot.wav"))
        throw std::runtime_error("No shoot.wav");
    if (!musicDeath.openFromFile("resources/death.wav"))
        throw std::runtime_error("No death.wav");

    std::cout << "Init sound success" << std::endl;
}
void Sound::playHit() {
    sound.setBuffer(bufferHit);
    sound.play();
}
void Sound::playLevelUp() {
    sound.setBuffer(bufferLevelUp);
    sound.play();
}
void Sound::playShoot() {
    sound.setBuffer(bufferShoot);
    sound.play();
}
void Sound::playDeath() {
    musicDeath.play();
}
}