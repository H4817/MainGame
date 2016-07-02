#pragma once
#include "Entity.h"

using namespace sf;
using namespace std;

struct EnemyBullet :public Entity {
public:
    int direction;
    float rotation;
    const Vector2f IMAGE_SIZE = {54, 25};
    Vector2f playerPos;
    float timer;
    int distance = 2000;
    EnemyBullet(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);
    void Update(float time, MapObjects &objects);
};