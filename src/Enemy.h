#pragma once
#include "EntityLogic.h"


using namespace sf;
using namespace std;

struct Enemy :public EntityLogic {
public:
    Enemy(MapObjects &objects, Level &lvl, String Name, std::list<EntityVisual*> visual);
    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);
    void update(float time, MapObjects & objects, std::list<EntityVisual*> & visual);
};