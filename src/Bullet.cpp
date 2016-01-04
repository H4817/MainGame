#include "Bullet.h"



Bullet::Bullet(Image &image, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name) : Entity(image,
                                                                                                                Position,
                                                                                                                Size,
                                                                                                                Name) {
    g_objects.obj = lvl.GetObjects("solid");
    position = Position;
    speed = 0.1;
    tempx = temp.x;
    tempy = temp.y;
    size = Size;
    alive = true;
    boost.x = position.x;
    boost.y = position.y;
    alive = true;
    Dx = tempx - position.x;
    Dy = tempy - position.y;
    rotation = (atan2(Dy, Dx)) * g_parameters.ANGLE / M_PI;
}

void Bullet::update(float time) {
    position.x += speed * (tempx - boost.x);
    position.y += speed * (tempy - boost.y);

    if (position.x <= 0)
        position.x = 1;

    if (position.y <= 0)
        position.y = 1;

    for (int i = 0; i < g_objects.obj.size(); i++) {
        if (getRect().intersects(g_objects.obj[i].rect)) {
            alive = false;
        }
    }
    sprite.setRotation(rotation);
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}
