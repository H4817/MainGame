#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Enemy :public Entity {
public:
    Enemy(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f &temp, String Name);
    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);
    void update(float time, MapObjects & objects);
    void Animation();
    void CreateNewReward();
    void CreateNewExplosion(const float & time);
private:
    float m_frameCounter;

    Texture m_explosionTexture;
    Texture m_shieldRewardTexture;
    Texture m_healthRewardTexture;
    enum States
    {
        ALIVE,
        DEATH
    };

    States m_state;
    float m_rotation;
    bool isMove;
    Vector2f playerPos;
};