#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Bullet :public Entity {
public:
    Parameters parameters;
    MapObjects objects;
    int direction;
    float tempy;
    float tempx;
    float rotation;
    float Dx;
    float Dy;
    Bullet(Image &image, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);
    void update(float time);
};