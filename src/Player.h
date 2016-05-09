#pragma once

#include "Entity.h"


using namespace sf;
using namespace std;

struct Player : public Entity {
public:
    //int counter = 0;
    float rotation;
    PlayerProperties playerProperties;
    int playerScore;
    int health;
    const Vector2f ImageSize = {79, 99};


    Vector2f acceleration;
    Vector2f m_temp;
    float distance;


    Player(Image &image, MapObjects &objects, Level &lev, Vector2f Position, Vector2i Size, String Name);

    void control(const float &time);

    void rotation_GG(Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects);

    void update(float time, MapObjects &objects);

private:
    enum {
        MOVE, SLIDE, STAY
    } state;
    //   Texture m_shipTexture;
    // Sprite m_shipWithoutThrust;
    // Sprite m_shipWithThrust;

};