#include "Bullet.h"

bool IsOutsideOfDistance(const Vector2f &playerPos, const Vector2f &position, size_t distance) {
    return (position.x > playerPos.x + distance || position.x < playerPos.x - distance) ||
           (position.y > playerPos.y + distance || position.y < playerPos.y - distance);
}

Bullet::Bullet(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f targetPosition,
               String Name) : Entity(image, Position, Size, Name) {
    speed = 0.03;
    Entity::temp = targetPosition;
    boost = {position.x, position.y};
    rotation = (atan2(targetPosition.y - position.y, targetPosition.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
}

void Bullet::Update(float time, MapObjects &objects) {
    position += (temp - boost) * speed;
    if (IsOutsideOfDistance(playerPos, position, distance)) {
        alive = false;
    }
    sprite.setRotation(rotation);
    sprite.setPosition(position.x + 39.5 * (cos(rotation * M_PI / 180)) + size.x / 2,
                       position.y + 49.5 * (sin(rotation * M_PI / 180)) + size.y / 2);
}

Rocket::Rocket(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
               String Name) : Entity(image, Position, Size, Name) {
    speed = 0.01;
    Entity::temp = temp;
    boost = {position.x, position.y};
    rotation = (atan2(temp.y - position.y, temp.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
    m_explosionTexture.loadFromFile("IMG/Exp_type_A1.png");
    m_frameCounter = 0;
}

void Rocket::CreateExplosion(const float &time) {
    ExplosionAnimation(time);
    if (m_frameCounter >= 42) {
        alive = false;
    }
}

void Rocket::Update(float time, MapObjects &objects) {
    if (name != "explosion") {
        position += (temp - boost) * speed;
        if (IsOutsideOfDistance(playerPos, position, distance)) {
            name = "explosion";
        }
        sprite.setRotation(rotation);
        sprite.setPosition(position.x + 39.5 * (cos(rotation * M_PI / 180)) + size.x / 2,
                           position.y + 49.5 * (sin(rotation * M_PI / 180)) + size.y / 2);
    }
    else {
        CreateExplosion(time);
    }
}

void Rocket::ExplosionAnimation(const float &time) {
    m_frameCounter += 0.054 * time;
    sprite.setTextureRect(IntRect(128 * int(m_frameCounter), 0, 128, 128));
    sprite.setTexture(m_explosionTexture);
}

SmartRocket::SmartRocket(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
                         String Name) : Rocket(image, objects, lvl, Position, Size, temp, Name) {
    speed = 0.01;
    Entity::temp = temp;
    boost = {position.x, position.y};
    rotation = (atan2(temp.y - position.y, temp.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
    m_explosionTexture.loadFromFile("IMG/Exp_type_C1.png");
    m_frameCounter = 0;
    m_playerCoordinates = &objects.playerPosition;
}

void SmartRocket::Update(float time, MapObjects &objects) {
    if (name != "explosion") {
        rotation = static_cast<float>(
                (atan2(m_playerCoordinates->y - position.y, m_playerCoordinates->x - position.x)) *
                parameters.ANGLE / M_PI);
        if (!IsOutsideOfDistance(playerPos, position, distance)) {
            velocity += {static_cast<float>(ACCELERATION * time * (m_playerCoordinates->x - position.x) / distance),
                         static_cast<float>(ACCELERATION * time * (m_playerCoordinates->y - position.y) / distance)};
            sprite.setRotation(rotation);
            position.x += velocity.x;
            position.y += velocity.y;
            sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
        }
        else {
            name = "explosion";
        }
    }
    else {
        CreateExplosion(time);
    }
}

void SmartRocket::CreateExplosion(const float &time) {
    ExplosionAnimation(time);
    if (m_frameCounter >= 49) {
        alive = false;
    }
}

void SmartRocket::ExplosionAnimation(const float &time) {
    m_frameCounter += 0.054 * time;
    sprite.setTextureRect(IntRect(128 * int(m_frameCounter), 0, 124, 124));
    sprite.setTexture(m_explosionTexture);
}
