#pragma once
#include "Entity.h"

struct Bullet :public Entity {
public:
    Bullet(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);
    void Update(float time, MapObjects &objects);

private:
    Vector2f playerPos;
    const size_t distance = 2000;
    const Vector2f IMAGE_SIZE = {54, 25};
    float rotation;
};