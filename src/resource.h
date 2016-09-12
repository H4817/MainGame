#pragma once

#include <SFML/Graphics.hpp>

struct SimpleRocket {
    const sf::Vector2i SIZE = {49, 14};
    const size_t DAMAGE = 60;
};

struct PlayerBullet {
    const sf::Vector2i SIZE = {54, 25};
    const size_t DAMAGE = 15;
};

struct PlayerProperties {
    const sf::Vector2i SIZE = {79, 99};
    const size_t HEALTH = 300;
    size_t shield = 500;
    const float SPEED = 0.2;
    PlayerBullet playerBullet;
    SimpleRocket simpleRocket;
};

struct Parameters {
    const std::pair<unsigned, unsigned> WINDOW_SIZE = {sf::VideoMode::getDesktopMode().width,
                                                       sf::VideoMode::getDesktopMode().height};
    const size_t ANGLE = 180;
};

struct EasyEnemyBullet {
    const sf::Vector2i SIZE = {54, 25};
    const size_t DAMAGE = 20;
};

struct _SmartRocket {
    const sf::Vector2i SIZE = {60, 16};
    const size_t DAMAGE = 80;
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
    const sf::Vector2i SIZE = {114, 102};
    const size_t COLLISION_DAMAGE = 3;
    const size_t AGGRO_DISTANCE = 1000;
    SimpleRocket simpleRocket;
};

struct HardEnemy {
    size_t health = 500;
    const sf::Vector2i SIZE = {150, 150};
    const size_t COLLISION_DAMAGE = 3;
    const size_t AGGRO_DISTANCE = 1500;
    _SmartRocket smartRocket;
};

struct EnemiesHandler {
    EasyEnemy easyEnemy;
    MediumEnemy mediumEnemy;
    HardEnemy hardEnemy;
};

struct MapObjects {
    std::vector<Object> obj;
    sf::Vector2f playerPosition;
    float playerRotation;
};