#pragma once
#include <SFML/Graphics.hpp>

struct Bullet {
    sf::RectangleShape shape;
    bool active = false;

    Bullet(float x, float y);
    void update(float dt);
};