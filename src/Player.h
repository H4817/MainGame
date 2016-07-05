#pragma once

#include "Entity.h"

struct Player : public Entity {
public:

    int health;

    Player(Image &image, MapObjects &objects, Level &lev, sf::Vector2f Position, sf::Vector2i Size, String Name);

    void control(const float &time);

    void rotation_GG(sf::Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects);

    void Update(float time, MapObjects &objects);

private:
    const size_t MAX_HP = 200;
    float rotation;
    const sf::Vector2f ImageSize = {79, 99};
    sf::Vector2f m_temp;
    float distance;
    enum {
        MOVE, SLIDE, STAY
    } state;
};