#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Bullet :public Entity {
public:
    int direction;
    float rotation;
    Bullet(Image &image, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);
    void update(float time);
};