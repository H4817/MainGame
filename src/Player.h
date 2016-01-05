#pragma once

#include "Entity.h"


using namespace sf;
using namespace std;

struct Player : public Entity {
public:
    PlayerProperties playerProperties;
    Parameters parameters;
    MapObjects objects;
    enum {
        left, right, up, down, leftUp, rightUp, leftDown, rightDown, stay
    } state;
    float rotation;
    int playerScore;

    Player(Image &image, Level &lev, Vector2f Position, Vector2i Size, String Name);

    void control();

    void rotation_GG(Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy);

    void update(float time);
};