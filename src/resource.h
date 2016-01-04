#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;


struct PlayerProperties {
    const Vector2i SIZE = {147, 125};
    const int HEALTH = 100;
    const float SPEED = 0.2;
};

PlayerProperties g_playerProperties;

struct Parameters {
    const unsigned WINDOW_SIZE_X = 1680;
    const unsigned WINDOW_SIZE_Y = 1050;
    const unsigned ANGLE = 180;
};

Parameters g_parameters;

struct PlayerBullet {
    const Vector2i SIZE = {100, 14};
    const unsigned DAMAGE = 10;
};

PlayerBullet g_playerBullet;

struct EasyEnemy {
    const Vector2i SIZE = {74, 67};
    const unsigned DAMAGE = 1;
    const float SPEED = 0.1;
};

EasyEnemy g_easyEnemy;

struct MapObjects {
    std::vector<Object> obj;
};

MapObjects g_objects;