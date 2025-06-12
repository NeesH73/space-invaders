#pragma once
#include <SFML/System.hpp>

// Глобальные настройки
const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_LEVEL = 3;

// Конфигурация уровней
struct LevelConfig {
    int rows;
    int cols;
    float enemySpeed;
    float fireCooldown;
};

extern const LevelConfig LEVELS[MAX_LEVEL];

// Константы скорости
const float PLAYER_SPEED = 300.f;
const float ENEMY_SPEED = 40.f;
const float BULLET_SPEED = 500.f;
const float ENEMY_BULLET_SPEED = 300.f;
const float FIRE_COOLDOWN = 0.5f;
const float ENEMY_FIRE_COOLDOWN = 1.5f;