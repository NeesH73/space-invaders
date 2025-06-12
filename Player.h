#pragma once
#include <SFML/Graphics.hpp>
#include "GameConfig.h"

struct Player {
    sf::RectangleShape ship;
    float speed = PLAYER_SPEED;

    Player();
    void moveLeft(float dt);
    void moveRight(float dt);
};