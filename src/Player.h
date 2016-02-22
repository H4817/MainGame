#pragma once

#include "Entity.h"


using namespace sf;
using namespace std;

struct Player : public Entity {
public:
    enum {
        left, right, up, down, leftUp, rightUp, leftDown, rightDown, stay
    } state;
    float rotation;
    int playerScore;
    int health = playerProperties.HEALTH;
    const Vector2f ImageSize = {79, 99};
    Player(Image &image, MapObjects & objects, Level &lev, Vector2f Position, Vector2i Size, String Name);

    void control();

    void rotation_GG(Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);

    void update(float time, MapObjects & objects);
};