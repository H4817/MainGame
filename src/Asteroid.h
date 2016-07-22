#pragma once

#include "Entity.h"

class Asteroid : public Entity {
public:
    Asteroid(Image &image, Vector2f Position, Vector2i Size, String Name);

    void Update(float time, MapObjects &objects);

    void Animation(float time);

private:
    Texture m_explosionTexture;
    int health;
    const Vector2f IMAGE_SIZE = {65, 64};
};


