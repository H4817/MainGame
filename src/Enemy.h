#pragma once

#include "Entity.h"

class IEnemy {
public:
    virtual void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) = 0;

    virtual void Update(float time, MapObjects &objects) = 0;

    virtual void CreateNewReward() = 0;

    virtual void ExplosionAnimation(const float &time) = 0;
};

class CEasyEnemy : public Entity, public IEnemy {
public:

    CEasyEnemy(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f &temp,
               String Name);

    virtual void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects);

    virtual void Update(float time, MapObjects &objects);

    virtual void CreateNewReward();

    virtual void ExplosionAnimation(const float &time);

protected:
    const size_t MAX_HEALTH = 200;
    bool m_isAggro;
    float distance;
    float m_frameCounter;
    Vector2f *m_playerCoordinates;
    Texture m_explosionTexture;
    Texture m_shieldRewardTexture;
    Texture m_healthRewardTexture;
    float m_rotation;
};

class CMediumEnemy : public CEasyEnemy {
public:

    CMediumEnemy(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f &temp,
                 String Name);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects);

    void Update(float time, MapObjects &objects);

    void CreateNewReward();

    void ExplosionAnimation(const float &time);

};
