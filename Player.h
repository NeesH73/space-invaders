#pragma once
#include <SFML/Graphics.hpp>

struct Player {
    sf::RectangleShape ship;
    float speed = 300.f;

    Player();
};
