#pragma once
#include "EntityLogic.h"


using namespace sf;
using namespace std;

struct Bullet :public EntityLogic, public EntityVisual {
public:
    EntityVisual *visual;
    int direction;
    float rotation;
    Bullet(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);
    void update(float time, MapObjects & objects);
};