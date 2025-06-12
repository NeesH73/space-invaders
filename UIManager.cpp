#include "UIManager.h"
#include "GameConfig.h"
#include <iostream>

GameState showMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
        std::cerr << "[ERROR] Failed to load font!" << std::endl;
        return GameState::GAME_OVER;
    }

    const float centerX = static_cast<float>(WIDTH / 2);
    const float centerY = static_cast<float>(HEIGHT / 2);

    sf::Text title("Space Invaders", font, 40);
    sf::Text playButton("Start Game", font, 30);
    sf::Text exitButton("Exit", font, 30);

    title.setFillColor(sf::Color::Cyan);
    playButton.setFillColor(sf::Color::White);
    exitButton.setFillColor(sf::Color::White);

    title.setPosition(centerX - title.getGlobalBounds().width / 2, 100);
    playButton.setPosition(centerX - playButton.getGlobalBounds().width / 2, 300);
    exitButton.setPosition(centerX - exitButton.getGlobalBounds().width / 2, 350);

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

                if (playBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                    return GameState::PLAYING;
                }
                else if (exitBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
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

GameState showVictoryScreen(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
        std::cerr << "[ERROR] Failed to load font!" << std::endl;
        return GameState::MENU;
    }

    sf::Text winText("You Win!", font, 50);
    winText.setFillColor(sf::Color::Green);
    winText.setPosition(WIDTH / 2 - winText.getGlobalBounds().width / 2, HEIGHT / 2 - 100);

    sf::Text nextLevelButton("Next Level", font, 30);
    nextLevelButton.setFillColor(sf::Color::White);
    nextLevelButton.setPosition(WIDTH / 2 - nextLevelButton.getGlobalBounds().width / 2, HEIGHT / 2);

    sf::Text mainMenuButton("Main Menu", font, 30);
    mainMenuButton.setFillColor(sf::Color::White);
    mainMenuButton.setPosition(WIDTH / 2 - mainMenuButton.getGlobalBounds().width / 2, HEIGHT / 2 + 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return GameState::MENU;

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::FloatRect nextBounds = nextLevelButton.getGlobalBounds();
                sf::FloatRect mainBounds = mainMenuButton.getGlobalBounds();

                if (nextBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                    window.close();
                    window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
                    window.setFramerateLimit(60);
                    return GameState::PLAYING;
                }
                else if (mainBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                    return GameState::MENU;
                }
            }
        }

        window.clear();
        window.draw(winText);
        window.draw(nextLevelButton);
        window.draw(mainMenuButton);
        window.display();
    }

    return GameState::MENU;
}

GameState showGameOverScreen(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/tahoma.ttf")) {
        std::cerr << "[ERROR] Failed to load font!" << std::endl;
        return GameState::MENU;
    }

    sf::Text gameOverText("You Lose!", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(WIDTH / 2 - gameOverText.getGlobalBounds().width / 2, HEIGHT / 2 - 25);

    sf::Text restartButton("Restart", font, 30);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(WIDTH / 2 - restartButton.getGlobalBounds().width / 2, HEIGHT / 2 + 50);

    sf::Text mainMenuButton("Main Menu", font, 30);
    mainMenuButton.setFillColor(sf::Color::White);
    mainMenuButton.setPosition(WIDTH / 2 - mainMenuButton.getGlobalBounds().width / 2, HEIGHT / 2 + 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return GameState::MENU;

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::FloatRect restartBounds = restartButton.getGlobalBounds();
                sf::FloatRect mainBounds = mainMenuButton.getGlobalBounds();

                if (restartBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                    window.close();
                    window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
                    window.setFramerateLimit(60);
                    return GameState::PLAYING;
                }
                else if (mainBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                    return GameState::MENU;
                }
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(restartButton);
        window.draw(mainMenuButton);
        window.display();
    }

    return GameState::MENU;
}