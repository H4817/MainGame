#include "Bullet.h"


Bullet::Bullet(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
               String Name) : Entity(image,
                                     Position,
                                     Size,
                                     Name) {
    objects.obj = lvl.GetObjects("solid");
    speed = 0.03;
    Entity::temp = temp;
    boost = {position.x, position.y};
    rotation = (atan2(temp.y - position.y, temp.x - position.x)) * parameters.ANGLE / M_PI;
    playerPos = Position;
}

void Bullet::update(float time, MapObjects &objects) {
    position += (temp - boost) * speed;
    if ((position.x > playerPos.x + distance || position.x < playerPos.x - distance) ||
        (position.y > playerPos.y + distance || position.y < playerPos.y - distance)) {
        alive = false;
    }

    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect().intersects(objects.obj[i].rect)) {
            alive = false;
        }
    }
    sprite.setRotation(rotation);
    sprite.setPosition(position.x + 71.5 * (cos(rotation * M_PI / 180)) + size.x / 2, position.y + 61.5 * (sin(rotation * M_PI / 180)) + size.y / 2);

}
