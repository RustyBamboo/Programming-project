#include "player.h"

Player::Player() : Entity(50,3, sf::Vector2f(50,100)){

}

void Player::move() {
	std::cout<<"move"<<std::endl;
}