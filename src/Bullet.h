#pragma once
#include "EntityLogic.h"


using namespace sf;
using namespace std;

struct Bullet :public EntityLogic {
public:
    int direction;
    float rotation;
    Bullet(MapObjects & objects, Level & lvl, Vector2f temp, String Name, std::list<EntityVisual*> visual);
    void update(float time, MapObjects & objects, std::list<EntityVisual*> & visual);
};