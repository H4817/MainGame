#include "Enemy.h"


Enemy::Enemy(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp,
             String Name) : Entity(
        image, Position, Size, Name) {
    objects.obj = lvl.GetObjects("solid");
    EnemyPos = Position;
    if (name == "easyEnemy") {
        speed = 0.001;
        boost = {position.x, position.y};
        Entity::temp1 = temp;
        rotation = (atan2(temp1.y - position.y, temp1.x - position.x)) * parameters.ANGLE / M_PI;
        sprite.setTextureRect(IntRect(0, 0, size.x, size.y));

    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect().intersects(objects.obj[i].rect)) {
            if (objects.obj[i].name == "solid") {
                if (Dy > 0) {
                    position.y = objects.obj[i].rect.top - size.y;
                    boost.y = -easyEnemy.speed.y;
                }
                if (Dy < 0) {
                    position.y = objects.obj[i].rect.top + objects.obj[i].rect.height;
                    boost.y = easyEnemy.speed.y;
                }
                if (Dx > 0) {
                    position.x = objects.obj[i].rect.left - size.x;
                    boost.x = -easyEnemy.speed.x;
                }
                if (Dx < 0) {
                    position.x = objects.obj[i].rect.left + objects.obj[i].rect.width;
                    boost.x = easyEnemy.speed.x;
                }
            }
        }
    }
}

void Enemy::update(float time, MapObjects &objects) {
    if (name == "easyEnemy") {
        sprite.setRotation(rotation);
        checkCollisionWithMap(boost.x, boost.y, objects);
        if (position.x >= 100 && position.y >= 100) {

            position += (temp1 - boost) * speed;
            sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
        }

        if (healthEasyEnemy <= 0) {
            alive = false;
        }
    }
}
