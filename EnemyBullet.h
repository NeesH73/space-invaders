#pragma once
#include <SFML/Graphics.hpp>

struct EnemyBullet {
    sf::RectangleShape shape;
    bool active = false;

    EnemyBullet(float x, float y);
    void update(float dt);
};