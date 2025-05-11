#include "EnemyBullet.h"
#include "GameConfig.h"

EnemyBullet::EnemyBullet(float x, float y) {
    shape.setSize(sf::Vector2f(6, 15));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
    active = true;
}

void EnemyBullet::update(float dt) {
    if (active) {
        float y = shape.getPosition().y + 300.f * dt;
        shape.setPosition(shape.getPosition().x, y);

        if (y > HEIGHT) active = false;
    }
}