#pragma once
#include <SFML/Graphics.hpp>

struct Enemy {
    sf::RectangleShape shape;
    bool active = true;

    Enemy(float x, float y);
};