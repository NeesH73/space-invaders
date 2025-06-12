#include "Player.h"

Player::Player() {
    ship.setSize({ 50, 20 });
    ship.setFillColor(sf::Color::Green);
    ship.setPosition(WIDTH / 2 - 25, HEIGHT - 50);
}

void Player::moveLeft(float dt) {
    if (ship.getPosition().x > 0) {
        ship.move(-speed * dt, 0);
    }
}

void Player::moveRight(float dt) {
    if (ship.getPosition().x < WIDTH - 50) {
        ship.move(speed * dt, 0);
    }
}