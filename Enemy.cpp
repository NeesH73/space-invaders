#include "Enemy.h"

Enemy::Enemy(float x, float y) {
    shape.setSize({ 40, 20 });
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}