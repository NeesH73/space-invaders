#pragma once
#include <SFML/Graphics.hpp>

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    VICTORY  
};

GameState showMenu(sf::RenderWindow& window);