#pragma once

#include "Entity.h"

struct Player : public Entity {
public:

    Player(Image &image, sf::Vector2f Position, sf::Vector2i Size, String Name);

    void control(const float &time);

    void rotation_GG(sf::Vector2f pos);

    void checkCollisionWithMap(float Dx, float Dy, MapObjects &objects);

    void Update(float time, MapObjects &objects);

    int GetState();

    size_t GetAmountOfMissile();

    void SetAmountOfMissile(size_t amount);

    size_t GetCurrentWeapon();

    void SetCurrentWeapon(size_t weaponNumber);

private:
    enum CurrentWeapon
    {
        BULLET,
        MISSILE
    };
    CurrentWeapon currentWeapon;
    PlayerProperties playerProperties;
    const size_t MAX_HP = playerProperties.HEALTH;
    float rotation;
    const double ACCELERATION = 0.001;
    const double DECELERATION = 0.997;
    const sf::Vector2f ImageSize = {79, 99};
    size_t amountOfMissile;
    sf::Vector2f m_temp;
    float distance;
    enum {
        MOVE, SLIDE, STAY
    } state;
};