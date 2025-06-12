#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "UIManager.h"
#include "GameConfig.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
    if (!window.isOpen()) return -1;

    // Загрузка значка
    sf::Image icon;
    if (icon.loadFromFile("assets/icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    window.setFramerateLimit(60);

    while (true) {
        GameState state = showMenu(window);

        if (state == GameState::PLAYING) {
            window.setVisible(false);
            window.create(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
            window.setFramerateLimit(60);
            runGame(window);
        }
        else {
            break;
        }
    }

    return 0;
}