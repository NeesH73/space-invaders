#include "Enemy.h"

Enemy::Enemy(float x, float y) {
    shape.setSize(sf::Vector2f(40, 20));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}