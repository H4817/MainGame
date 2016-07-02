#pragma once
#include <SFML/Graphics.hpp>

struct PlayerProperties {
    const sf::Vector2i SIZE = {79, 99};
    const size_t HEALTH = 200;
    int shield = 200;
    const float SPEED = 0.2;
    sf::Vector2f position;
};

struct Parameters {
    const std::pair<unsigned, unsigned> WINDOW_SIZE = {1680, 1050};
    const size_t ANGLE = 180;
    const std::pair<size_t, size_t> MAP_SIZE = {3120, 3028};
};

struct PlayerBullet {
    const sf::Vector2i SIZE = {54, 25};
    const size_t DAMAGE = 10;
};

struct EasyEnemy {
    size_t health = 200;
    const sf::Vector2i SIZE = {72, 66};
    const size_t COLLISION_DAMAGE = 2;
};

struct MapObjects {
    std::vector<Object> obj;
    sf::Vector2f playerPosition;
};