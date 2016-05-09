#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Enemy :public Entity {
public:

    Enemy(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f &temp, String Name);
    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);
    void update(float time, MapObjects & objects);
    void CreateNewReward();
    void ExplosionAnimation(const float &time);
private:
    bool m_isAggro;
    float distance;
    float m_frameCounter;
    //pair <int, int> * m_playerCoordinates;
    Vector2f *m_playerCoordinates;
    Texture m_explosionTexture;
    Texture m_shieldRewardTexture;
    Texture m_healthRewardTexture;
    float m_rotation;
    bool isMove;
    Vector2f playerPos;
};