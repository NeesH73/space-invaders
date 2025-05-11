#include "Player.h"
#include "GameConfig.h"

Player::Player() {
    ship.setSize(sf::Vector2f(50, 20));
    ship.setFillColor(sf::Color::Green);
    ship.setPosition(WIDTH / 2 - 25, HEIGHT - 50);
}