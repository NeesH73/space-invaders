#include "Bullet.h"

Bullet::Bullet(float x, float y) {
    shape.setSize(sf::Vector2f(6, 15));
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
    active = true;
}

void Bullet::update(float dt) {
    if (active) {
        float y = shape.getPosition().y - 500.f * dt;
        shape.setPosition(shape.getPosition().x, y);

        if (y < 0) active = false;
    }
}