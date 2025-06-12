#include "EnemyBullet.h"
#include "GameConfig.h"


EnemyBullet::EnemyBullet(float x, float y) {
    shape.setSize({ 6, 15 });
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
    active = true;
}

void EnemyBullet::update(float dt) {
    if (active) {
        float y = shape.getPosition().y + ENEMY_BULLET_SPEED * dt;
        shape.setPosition(shape.getPosition().x, y);

        if (y > HEIGHT) active = false;
    }
}