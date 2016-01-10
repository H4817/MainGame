#include "Enemy.h"
#include "resource.h"


Enemy::Enemy(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, String Name) : Entity(
        image, Position, Size, Name) {
    objects.obj = lvl.GetObjects("solid");
    if (name == "easyEnemy") {
        sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
        sprite.rotate(parameters.ANGLE);
        boost.x = -easyEnemy.SPEED;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect().intersects(objects.obj[i].rect)) {
            if (objects.obj[i].name == "solid") {
                if (Dy > 0) {
                    position.y = objects.obj[i].rect.top - size.y;
                    boost.y = -easyEnemy.SPEED;
                }
                if (Dy < 0) {
                    position.y = objects.obj[i].rect.top + objects.obj[i].rect.height;
                    boost.y = easyEnemy.SPEED;
                }
                if (Dx > 0) {
                    position.x = objects.obj[i].rect.left - size.x;
                    boost.x = -easyEnemy.SPEED;
                }
                if (Dx < 0) {
                    position.x = objects.obj[i].rect.left + objects.obj[i].rect.width;
                    boost.x = easyEnemy.SPEED;
                }
            }
        }
    }
}

void Enemy::update(float time, MapObjects &objects) {
    if (name == "easyEnemy") {
        checkCollisionWithMap(boost.x, boost.y, objects);
        position += boost * time;
        sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
        if (healthEasyEnemy <= 0) {
            alive = false;
        }
    }
}
