#pragma once

#include "Entity.h"

class IEnemy {
public:
    virtual void Update(float time, MapObjects &objects) = 0;

    virtual void CreateNewReward() = 0;

    virtual void ExplosionAnimation(const float &time) = 0;

    virtual void ProcessState() = 0;
};

class CEasyEnemy : public Entity, public IEnemy {
public:

    CEasyEnemy(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f &temp,
               String Name);

    virtual void Update(float time, MapObjects &objects);

    virtual void CreateNewReward();

    virtual void ExplosionAnimation(const float &time);

    virtual void ProcessState();

protected:
    Texture withoutThrust;
    Texture withThrust;
    const double ACCELERATION = 0.003;
    const double DECELERATION = 0.985;
    bool m_isAggro;
    float distance;
    float m_frameCounter;
    size_t min_distance;
    size_t MAX_HEALTH;
    size_t AGGRO_DISTANCE;
    Vector2f *m_playerCoordinates;
    Texture m_explosionTexture;
    Texture m_shieldRewardTexture;
    Texture m_healthRewardTexture;
    float m_rotation;
    EnemiesHandler enemiesHandler;
    enum {
        MOVE, SLIDE, STAY
    } state;
};

class CMediumEnemy : public CEasyEnemy {
public:
    CMediumEnemy(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f &temp,
                 String Name);


    void Update(float time, MapObjects &objects);

    void CreateNewReward();

    void ExplosionAnimation(const float &time);

    void ProcessState();
};

class CStrongEnemy : public CMediumEnemy {
public:
    CStrongEnemy(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f &temp,
                 String Name);
};
