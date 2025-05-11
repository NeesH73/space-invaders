#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Collision.h"
#include "GameConfig.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Главное меню
GameState showMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
        return GameState::GAME_OVER;
    }

    sf::Text title("Space invaders", font, 40);
    sf::Text playButton("Start Game", font, 30);
    sf::Text exitButton("Exit", font, 30);

    title.setFillColor(sf::Color::Cyan);
    playButton.setFillColor(sf::Color::White);
    exitButton.setFillColor(sf::Color::White);

    title.setPosition(WIDTH / 2 - title.getGlobalBounds().width / 2, 100);
    playButton.setPosition(WIDTH / 2 - playButton.getGlobalBounds().width / 2, 300);
    exitButton.setPosition(WIDTH / 2 - exitButton.getGlobalBounds().width / 2, 350);

    int selectedItem = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return GameState::GAME_OVER;

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                    selectedItem = 1 - selectedItem;
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedItem == 0)
                        return GameState::PLAYING;
                    else
                        return GameState::GAME_OVER;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::FloatRect playBounds = playButton.getGlobalBounds();
                sf::FloatRect exitBounds = exitButton.getGlobalBounds();

                if (playBounds.contains(mouse.x, mouse.y)) {
                    return GameState::PLAYING;
                }
                else if (exitBounds.contains(mouse.x, mouse.y)) {
                    return GameState::GAME_OVER;
                }
            }
        }

        playButton.setFillColor(selectedItem == 0 ? sf::Color::Yellow : sf::Color::White);
        exitButton.setFillColor(selectedItem == 1 ? sf::Color::Yellow : sf::Color::White);

        window.clear();
        window.draw(title);
        window.draw(playButton);
        window.draw(exitButton);
        window.display();
    }

    return GameState::GAME_OVER;
}

// Точка входа
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space invaders");
    window.setFramerateLimit(60);

    while (true) {
        GameState state = showMenu(window);

        if (state == GameState::PLAYING) {
            window.setVisible(false);
            window.create(sf::VideoMode(800, 600), "Space invaders");
            window.setFramerateLimit(60);

            // Запуск игры
            runGame(window);
        }
        else {
            break;
        }
    }

    return 0;
}