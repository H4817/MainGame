#include "Bullet.h"

bool IsOutsideOfDistance(const Vector2f &playerPos, const Vector2f &position, size_t distance) {
    return (position.x > playerPos.x + distance || position.x < playerPos.x - distance) ||
           (position.y > playerPos.y + distance || position.y < playerPos.y - distance);
}

Bullet::Bullet(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
               String Name) : Entity(image, Position, Size, Name) {
    objects.obj = lvl.GetObjects("solid");
    speed = 0.03;
    Entity::temp = temp;
    boost = {position.x, position.y};
    rotation = (atan2(temp.y - position.y, temp.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
}

void Bullet::Update(float time, MapObjects &objects) {
    position += (temp - boost) * speed;
    if (IsOutsideOfDistance(playerPos, position, distance)) {
        alive = false;
    }
    for (int i = 0; i < objects.obj.size(); i++) {
        if (RetRect().intersects(objects.obj[i].rect)) {
            alive = false;
        }
    }
    sprite.setRotation(rotation);
    sprite.setPosition(position.x + 39.5 * (cos(rotation * M_PI / 180)) + size.x / 2,
                       position.y + 49.5 * (sin(rotation * M_PI / 180)) + size.y / 2);
}

Rocket::Rocket(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
               String Name) : Entity(image, Position, Size, Name) {
    objects.obj = lvl.GetObjects("solid");
    speed = 0.01;
    Entity::temp = temp;
    boost = {position.x, position.y};
    rotation = (atan2(temp.y - position.y, temp.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
    m_explosionTexture.loadFromFile("IMG/Exp_type_B1.png");
    m_frameCounter = 0;
}

void Rocket::Update(float time, MapObjects &objects) {
    if (name != "explosion") {
        position += (temp - boost) * speed;
        if (IsOutsideOfDistance(playerPos, position, distance)) {
            name = "explosion";
        }
        for (int i = 0; i < objects.obj.size(); i++) {
            if (RetRect().intersects(objects.obj[i].rect)) {
                name = "explosion";
            }
        }
        sprite.setRotation(rotation);
        sprite.setPosition(position.x + 39.5 * (cos(rotation * M_PI / 180)) + size.x / 2,
                           position.y + 49.5 * (sin(rotation * M_PI / 180)) + size.y / 2);
    }
    else {
        ExplosionAnimation(time);
        if (m_frameCounter > 64) {
            alive = false;
        }
    }
}

void Rocket::ExplosionAnimation(const float &time) {
    m_frameCounter += 0.054 * time;
    sprite.setTextureRect(IntRect(96 * int(m_frameCounter), 0, 96, 96));
    sprite.setTexture(m_explosionTexture);
}
