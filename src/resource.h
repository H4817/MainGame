#pragma once

#include <SFML/Graphics.hpp>

struct PlayerBullet {
    const sf::Vector2i SIZE = {54, 25};
    const size_t DAMAGE = 10;
};

struct PlayerProperties {
    const sf::Vector2i SIZE = {79, 99};
    const size_t HEALTH = 200;
    int shield = 200;
    const float SPEED = 0.2;
    PlayerBullet playerBullet;
};

struct Parameters {
    const std::pair<unsigned, unsigned> WINDOW_SIZE = {1680, 1050};
    const size_t ANGLE = 180;
    const std::pair<size_t, size_t> MAP_SIZE = {3120, 3028};
};

struct EasyEnemyBullet {
    const sf::Vector2i SIZE = {54, 25};
    const size_t DAMAGE = 10;
};

struct EasyEnemy {
    size_t health = 200;
    const sf::Vector2i SIZE = {80, 67};
    const size_t COLLISION_DAMAGE = 2;
    const size_t AGGRO_DISTANCE = 700;
    EasyEnemyBullet easyEnemyBullet;
};

struct MediumEnemy {
    size_t health = 300;
    const sf::Vector2i SIZE = {117, 100};
    const size_t COLLISION_DAMAGE = 3;
    const size_t AGGRO_DISTANCE = 900;
    EasyEnemyBullet easyEnemyBullet;
};

struct EnemiesHandler {
    EasyEnemy easyEnemy;
    MediumEnemy mediumEnemy;
};

struct MapObjects {
    std::vector<Object> obj;
    sf::Vector2f playerPosition;
};