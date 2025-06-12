#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Collision.h"
#include "GameConfig.h"

#include <list>
#include <vector>
#include <iostream>

void runGame(sf::RenderWindow& window) {
    int score = 0;
    int level = 0;

    while (level < MAX_LEVEL) {
        Player player;
        std::list<Bullet> bullets;
        std::list<EnemyBullet> enemyBullets;
        std::vector<Enemy> enemies;

        const LevelConfig& config = LEVELS[level];

        // Создание врагов
        const float startX = 100.f;
        const float startY = 50.f;
        const float spacingX = 60.f;
        const float spacingY = 40.f;

        for (int row = 0; row < config.rows; ++row) {
            for (int col = 0; col < config.cols; ++col) {
                enemies.emplace_back(startX + col * spacingX, startY + row * spacingY);
            }
        }

        sf::Clock clock;
        float enemyDirection = 1.f;
        float timeSinceLastShot = FIRE_COOLDOWN;
        float timeSinceEnemyShot = config.fireCooldown;

        // Текст для счёта и уровня
        sf::Font font;
        if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
            std::cerr << "[ERROR] Failed to load font!" << std::endl;
            return;
        }

        sf::Text scoreText("", font, 20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        sf::Text levelText("", font, 20);
        levelText.setFillColor(sf::Color::Cyan);
        levelText.setPosition(10, 40);

        bool isGameOver = false;

        while (window.isOpen() && !isGameOver) {
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

            // Стрельба игрока
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastShot >= FIRE_COOLDOWN) {
                bullets.emplace_back(player.ship.getPosition().x + 23, player.ship.getPosition().y - 10);
                timeSinceLastShot = 0.f;
            }

            // Обновление пуль игрока
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
            if (timeSinceEnemyShot >= config.fireCooldown && !enemies.empty()) {
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
                enemy.shape.move(config.enemySpeed * enemyDirection * dt, 0.f);

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
                        score += 100;
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

            // Проверка столкновений: враги с игроком
            for (const auto& enemy : enemies) {
                if (isColliding(enemy.shape, player.ship)) {
                    isGameOver = true;
                    break;
                }
            }

            // Проверка: враги спустились слишком низко
            for (const auto& enemy : enemies) {
                if (enemy.shape.getPosition().y + enemy.shape.getSize().y >= HEIGHT - 50) {
                    isGameOver = true;
                    break;
                }
            }

            // Проверка столкновений: пули врагов с игроком 
            for (const auto& ebullet : enemyBullets) {
                if (isColliding(ebullet.shape, player.ship)) {
                    isGameOver = true;
                    break;
                }
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

            // Отрисовка счёта и уровня
            scoreText.setString("Score: " + std::to_string(score));
            levelText.setString("Level: " + std::to_string(level + 1));

            window.draw(scoreText);
            window.draw(levelText);
            window.display();

            // Проверка победы
            if (enemies.empty()) {
                window.clear();
                sf::Text winText("You Win!", font, 50);
                winText.setFillColor(sf::Color::Green);
                winText.setPosition(WIDTH / 2 - winText.getGlobalBounds().width / 2, HEIGHT / 2 - 100);

                sf::Text nextLevelButton("Next Level", font, 30);
                nextLevelButton.setFillColor(sf::Color::White);
                nextLevelButton.setPosition(WIDTH / 2 - nextLevelButton.getGlobalBounds().width / 2, HEIGHT / 2);

                sf::Text mainMenuButton("Main Menu", font, 30);
                mainMenuButton.setFillColor(sf::Color::White);
                mainMenuButton.setPosition(WIDTH / 2 - mainMenuButton.getGlobalBounds().width / 2, HEIGHT / 2 + 50);

                window.draw(winText);
                window.draw(nextLevelButton);
                window.draw(mainMenuButton);
                window.display();

                // Обработка событий на экране победы
                while (true) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            return;

                        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse = sf::Mouse::getPosition(window);
                            sf::FloatRect nextBounds = nextLevelButton.getGlobalBounds();
                            sf::FloatRect mainBounds = mainMenuButton.getGlobalBounds();

                            if (nextBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                                level++;
                                if (level < MAX_LEVEL) {
                                    window.close();
                                    window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
                                    window.setFramerateLimit(60);
                                    goto RESTART;  // Переход на следующий уровень
                                }
                                else {
                                    return;  // Если все уровни пройдены
                                }
                            }

                            if (mainBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                                return;  // Возврат в главное меню
                            }
                        }
                    }
                }
            }

            // Проверка проигрыша
            if (isGameOver) {
                window.clear();
                sf::Text gameOverText("You Lose!", font, 50);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setPosition(WIDTH / 2 - gameOverText.getGlobalBounds().width / 2, HEIGHT / 2 - 25);
                window.draw(gameOverText);
                window.display();
                sf::sleep(sf::seconds(3));
                return;
            }
        }

    RESTART:
        continue;
    }
}