#include "Enemy.h"
#include "resource.h"


Enemy::Enemy(Image &image, MapObjects &objects, Level &lvl, Vector2f Position, Vector2i Size, String Name) : EntityLogic(
        Name, *visual), EntityVisual(image, Position, Size){
    objects.obj = lvl.GetObjects("solid");
    if (name == "easyEnemy") {
        visual.sprite.setTextureRect(IntRect(0, 0, visual.size.x, visual.size.y));
        visual.sprite.rotate(parameters.ANGLE);
        boost.x = -easyEnemy.SPEED;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect(visual).intersects(objects.obj[i].rect)) {
            if (objects.obj[i].name == "solid") {
                if (Dy > 0) {
                    visual.position.y = objects.obj[i].rect.top - visual.size.y;
                    boost.y = -easyEnemy.SPEED;
                }
                if (Dy < 0) {
                    visual.position.y = objects.obj[i].rect.top + objects.obj[i].rect.height;
                    boost.y = easyEnemy.SPEED;
                }
                if (Dx > 0) {
                    visual.position.x = objects.obj[i].rect.left - visual.size.x;
                    boost.x = -easyEnemy.SPEED;
                }
                if (Dx < 0) {
                    visual.position.x = objects.obj[i].rect.left + objects.obj[i].rect.width;
                    boost.x = easyEnemy.SPEED;
                }
            }
        }
    }
}

void Enemy::update(float time, MapObjects &objects) {
    if (name == "easyEnemy") {
        checkCollisionWithMap(boost.x, boost.y, objects);
        visual.position += boost * time;
        visual.sprite.setPosition(visual.position.x + visual.size.x / 2, visual.position.y + visual.size.y / 2);
        if (health <= 0) {
            alive = false;
        }
    }
}
