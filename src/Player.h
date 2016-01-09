#pragma once

#include "EntityLogic.h"



struct Player : public EntityLogic {
public:
    enum {
        left, right, up, down, leftUp, rightUp, leftDown, rightDown, stay
    } state;
    float rotation;
    int playerScore;

    Player(MapObjects & objects, Level &lev, String Name, std::list<EntityVisual*> visual);

    void control();

    void rotation_GG(Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);

    void update(float time, MapObjects & objects, std::list<EntityVisual*> & visual);
};