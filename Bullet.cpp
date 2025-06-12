#include "Bullet.h"
#include "GameConfig.h"

Bullet::Bullet(float x, float y) {
    shape.setSize({ 6, 15 });
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
    active = true;
}

void Bullet::update(float dt) {
    if (active) {
        float y = shape.getPosition().y - BULLET_SPEED * dt;
        shape.setPosition(shape.getPosition().x, y);

        if (y < 0) active = false;
    }
}