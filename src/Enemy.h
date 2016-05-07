#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Enemy :public Entity {
public:
    Enemy(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f &temp, String Name);
    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);
    void update(float time, MapObjects & objects);
    enum RewardsType
    {
        HEALTH,
        SHIELD
    };
    RewardsType m_rewardsType;
private:
    Texture m_shieldRewardTexture;
    Texture m_healthRewardTexture;
    enum States
    {
        ALIVE,
        EXPLOSION,
        REWARD
    };

    States m_state;
    float m_rotation;
    bool isMove;
    Vector2f EnemyPos;
    Vector2f playerPos;
};