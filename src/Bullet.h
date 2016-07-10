#pragma once

#include "Entity.h"

bool IsOutsideOfDistance(const Vector2f &playerPos, const Vector2f &position, size_t distance);

struct Bullet : public Entity {
public:
    Bullet(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f targetPosition,
           String Name);

    void Update(float time, MapObjects &objects);

private:
    Vector2f playerPos;
    const size_t distance = 2000;
    const Vector2f IMAGE_SIZE = {54, 25};
    float rotation;
};

class Rocket : public Entity {
public:
    Rocket(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);

    void Update(float time, MapObjects &objects);

protected:

    virtual void ExplosionAnimation(const float &time);

    virtual void CreateExplosion(const float &time);

protected:
    float m_frameCounter;
    Vector2f playerPos;
    const size_t distance = 1200;
    const Vector2f IMAGE_SIZE = {49, 14};
    float rotation;
    Texture m_explosionTexture;
};

class SmartRocket : public Rocket {
public:
    SmartRocket(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
                String Name);

    void Update(float time, MapObjects &objects);

private:
    void CreateExplosion(const float &time);

    void ExplosionAnimation(const float &time);

private:
    const double ACCELERATION = 0.005;
    Vector2f *m_playerCoordinates;
};
