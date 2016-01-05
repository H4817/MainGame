#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Enemy :public Entity {
public:
    EasyEnemy easyEnemy;
    Parameters parameters;
    MapObjects objects;
    Enemy(Image &image, Level &lvl, Vector2f Position, Vector2i Size, String Name);
    void checkCollisionWithMap(float Dx, float Dy);
    void update(float time);
};