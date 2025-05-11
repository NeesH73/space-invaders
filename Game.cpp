#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Collision.h"

const int WIDTH = 800;
const int HEIGHT = 600;

void runGame(sf::RenderWindow& window) {
    Player player;
    std::list<Bullet> bullets;
    std::list<EnemyBullet> enemyBullets;
    std::vector<Enemy> enemies;

    const int rows = 3;
    const int cols = 8;
    const float startX = 100.f;
    const float startY = 50.f;
    const float spacingX = 60.f;
    const float spacingY = 40.f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            enemies.emplace_back(startX + col * spacingX, startY + row * spacingY);
        }
    }

    sf::Clock clock;
    float enemyDirection = 1.f;
    float enemySpeed = 40.f;
    float fireCooldown = 0.5f;
    float timeSinceLastShot = fireCooldown;
    float enemyFireCooldown = 1.5f;
    float timeSinceEnemyShot = 0.f;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        timeSinceLastShot += dt;
        timeSinceEnemyShot += dt;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return;
        }

        // Управление игроком
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.ship.getPosition().x > 0)
            player.ship.move(-player.speed * dt, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.ship.getPosition().x < WIDTH - 50)
            player.ship.move(player.speed * dt, 0);

        // Стрельба
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastShot >= fireCooldown) {
            bullets.emplace_back(player.ship.getPosition().x + 23, player.ship.getPosition().y - 10);
            timeSinceLastShot = 0.f;
        }

        // Обновление пуль
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bulletIt->update(dt);
            if (!bulletIt->active) {
                bulletIt = bullets.erase(bulletIt);
            }
            else {
                ++bulletIt;
            }
        }

        // Стрельба врагов
        if (timeSinceEnemyShot >= enemyFireCooldown && !enemies.empty()) {
            int randomIndex = rand() % enemies.size();
            auto it = enemies.begin();
            std::advance(it, randomIndex);
            sf::Vector2f enemyPos = it->shape.getPosition();
            enemyBullets.emplace_back(enemyPos.x + 20, enemyPos.y + 20);
            timeSinceEnemyShot = 0.f;
        }

        // Обновление пуль врагов
        for (auto bulletIt = enemyBullets.begin(); bulletIt != enemyBullets.end();) {
            bulletIt->update(dt);
            if (!bulletIt->active) {
                bulletIt = enemyBullets.erase(bulletIt);
            }
            else {
                ++bulletIt;
            }
        }

        // Движение врагов
        bool hitLeft = false;
        bool hitRight = false;

        for (auto& enemy : enemies) {
            enemy.shape.move(enemySpeed * enemyDirection * dt, 0.f);

            if (enemy.shape.getPosition().x <= 0) {
                hitLeft = true;
            }
            else if (enemy.shape.getPosition().x + enemy.shape.getSize().x >= WIDTH) {
                hitRight = true;
            }
        }

        if (hitLeft || hitRight) {
            enemyDirection *= -1.f;
            for (auto& enemy : enemies) {
                enemy.shape.move(0, 10.f);
            }
        }

        // Проверка столкновений: пули с врагами
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bool hit = false;
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                if (isColliding(bulletIt->shape, enemyIt->shape)) {
                    enemyIt = enemies.erase(enemyIt);
                    bulletIt = bullets.erase(bulletIt);
                    hit = true;
                    break;
                }
                else {
                    ++enemyIt;
                }
            }
            if (!hit) ++bulletIt;
        }

        // Проверка столкновений: пули врагов с игроком 
        for (const auto& ebullet : enemyBullets) {
            if (isColliding(ebullet.shape, player.ship)) {
                return;
            }
        }

        // Победа
        if (enemies.empty()) {
            return;
        }

        // Отрисовка 
        window.clear();
        window.draw(player.ship);
        for (const auto& bullet : bullets) {
            window.draw(bullet.shape);
        }
        for (const auto& ebullet : enemyBullets) {
            window.draw(ebullet.shape);
        }
        for (const auto& enemy : enemies) {
            window.draw(enemy.shape);
        }
        window.display();
    }
}