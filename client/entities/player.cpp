#include "player.h"

Player::Player(){
	obj = new Polygon(30, 3);
	std::cout<<"Player generated"<<std::endl;
}


void Player::move() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		pos += sf::Vector2f(-0.1, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		pos += sf::Vector2f(0.1, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		pos += sf::Vector2f(0, -0.1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		pos += sf::Vector2f(0, 0.1);
	}
}