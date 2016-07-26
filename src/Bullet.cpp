#include "Bullet.h"

bool IsOutsideOfDistance(const Vector2f &playerPos, const Vector2f &position, size_t distance) {
    return (position.x > playerPos.x + distance || position.x < playerPos.x - distance) ||
           (position.y > playerPos.y + distance || position.y < playerPos.y - distance);
}

Bullet::Bullet(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f targetPosition,
               String Name) : Entity(image, Position, Size, Name) {
    speed = 20;
    Entity::temp = targetPosition;
    boost = position;
    rotation = (atan2(targetPosition.y - position.y, targetPosition.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
//    m_angle = (atan2f(targetPosition.y - position.y, targetPosition.x - position.x));
//    position = {position.x + ((54 + 25) / 2) * cos(rotation * DEG_TO_RAD),
//                position.y + ((74 + 25) ) * sin(rotation * DEG_TO_RAD)};
//    position = {100, 100};
//    std::cout << position.x << " " << position.y << "\n";
//    position =  {cos(rotation) * 10, sin(rotation) * 10};
//    std::cout << position.x << " " << position.y << "\n";
//    sprite.setPosition(position);
}

void Bullet::Update(float time, MapObjects &objects) {
    velocity.x = cos(rotation * DEG_TO_RAD) * speed;
    velocity.y = sin(rotation * DEG_TO_RAD) * speed;
    if (IsOutsideOfDistance(playerPos, position, distance)) {
        alive = false;
    }
    position += velocity;
    sprite.setRotation(rotation);
    sprite.setPosition(position);
}

Rocket::Rocket(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f temp,
               String Name) : Entity(image, Position, Size, Name) {
    speed = 10;
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
        velocity.x = cos(rotation * DEG_TO_RAD) * speed;
        velocity.y = sin(rotation * DEG_TO_RAD) * speed;
        if (IsOutsideOfDistance(playerPos, position, distance)) {
            name = "explosion";
        }
        position += velocity;
        sprite.setRotation(rotation);
        sprite.setPosition(position);
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

SmartRocket::SmartRocket(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f temp,
                         String Name) : Rocket(image, objects, Position, Size, temp, Name) {
    speed = 5;
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

            velocity.x = cos(rotation * DEG_TO_RAD) * speed;
            velocity.y = sin(rotation * DEG_TO_RAD) * speed;

            position += velocity;
            sprite.setRotation(rotation);
            sprite.setPosition(position);

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
