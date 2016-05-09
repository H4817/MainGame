#pragma once

#include "Entity.h"


using namespace sf;
using namespace std;

struct Player : public Entity {
public:
    enum {
        left, right, up, down, leftUp, rightUp, leftDown, rightDown, stay
    } state;
    bool isMOVE = false;
    float rotation;
    PlayerProperties playerProperties;
    int playerScore;
    int health = playerProperties.HEALTH;
    const Vector2f ImageSize = {79, 99};

    Player(Image &image, MapObjects &objects, Level &lev, Vector2f Position, Vector2i Size, String Name);

    //void CreateThrustAnimation(const float & time);

    void control();

    void rotation_GG(Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects);

    void update(float time, MapObjects &objects);

};