#pragma once
#include "Entity.h"


using namespace sf;
using namespace std;

struct Enemy :public Entity {
public:
    Texture texture1;
    Texture texture2;
    Texture texture3;
    Sprite explosion;
    Sprite shieldReward;
    Sprite healthReward;
    float rotation;
    bool isMove;
    Vector2f EnemyPos;
    Vector2f playerPos;
    Enemy(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name);
    void checkCollisionWithMap(float Dx, float Dy, MapObjects & objects);
    void update(float time, MapObjects & objects);
    void VisualPart();
};