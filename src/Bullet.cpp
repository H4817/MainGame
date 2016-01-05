#include "Bullet.h"



Bullet::Bullet(Image &image, MapObjects & objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name) : Entity(image,
                                                                                                                Position,
                                                                                                                Size,
                                                                                                                Name) {
    objects.obj = lvl.GetObjects("solid");
    position = Position;
    speed = 0.1;
    Entity::temp = temp;
    size = Size;
    alive = true;
    boost.x = position.x;
    boost.y = position.y;
    alive = true;
    rotation = (atan2(temp.y - position.y, temp.x - position.x)) * parameters.ANGLE / M_PI;
}

void Bullet::update(float time, MapObjects & objects) {
    position.x += speed * (temp.x - boost.x);
    position.y += speed * (temp.y - boost.y);

    if (position.x <= 0)
        position.x = 1;

    if (position.y <= 0)
        position.y = 1;

    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect().intersects(objects.obj[i].rect)) {
            alive = false;
        }
    }
    sprite.setRotation(rotation);
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}
