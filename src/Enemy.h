#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Enemy :public Entity {
public:

    Enemy(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f &temp, String Name);
    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);
    void Update(float time, MapObjects &objects);
    void CreateNewReward();
    void ExplosionAnimation(const float &time);
private:
    const size_t EASY_ENEMY_MAX_HEALTH = 200;
    bool m_isAggro;
    float distance;
    float m_frameCounter;
    Vector2f *m_playerCoordinates;
    Texture m_explosionTexture;
    Texture m_shieldRewardTexture;
    Texture m_healthRewardTexture;
    float m_rotation;
};