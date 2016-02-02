#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;


struct PlayerProperties {
    const Vector2i SIZE = {144, 124};
    const int HEALTH = 200;
    int shield = 200;
    const float SPEED = 0.2;
    Vector2f position;
};

struct Parameters {
    const unsigned WINDOW_SIZE_X = 1680;
    const unsigned WINDOW_SIZE_Y = 1050;
    const unsigned ANGLE = 180;
};

struct PlayerBullet {
    const Vector2i SIZE = {100, 14};
    const unsigned DAMAGE = 10;
};

struct EasyEnemy {
    int health = 200;
    const Vector2i SIZE = {72, 66};
    const unsigned DAMAGE = 1;
    Vector2f speed = {0.1, 0.1};
};

struct MapObjects {
    std::vector<Object> obj;
};