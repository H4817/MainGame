#include "Enemy.h"


Enemy::Enemy(MapObjects &objects, Level &lvl, String Name, std::list<EntityVisual*> visual) : EntityLogic(Name, Visual) {
    objects.obj = lvl.GetObjects("solid");
    if (name == "easyEnemy") {
        Visual->sprite.setTextureRect(IntRect(0, 0, Visual->size.x, Visual->size.y));
        Visual->sprite.rotate(parameters.ANGLE);
        boost.x = -easyEnemy.SPEED;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect(*Visual).intersects(objects.obj[i].rect)) {
            if (objects.obj[i].name == "solid") {
                if (Dy > 0) {
                    Visual->position.y = objects.obj[i].rect.top - Visual->size.y;
                    boost.y = -easyEnemy.SPEED;
                }
                if (Dy < 0) {
                    Visual->position.y = objects.obj[i].rect.top + objects.obj[i].rect.height;
                    boost.y = easyEnemy.SPEED;
                }
                if (Dx > 0) {
                    Visual->position.x = objects.obj[i].rect.left - Visual->size.x;
                    boost.x = -easyEnemy.SPEED;
                }
                if (Dx < 0) {
                    Visual->position.x = objects.obj[i].rect.left + objects.obj[i].rect.width;
                    boost.x = easyEnemy.SPEED;
                }
            }
        }
    }
}

void Enemy::update(float time, MapObjects &objects, std::list<EntityVisual*> & visual) {
    if (name == "easyEnemy") {
        checkCollisionWithMap(boost.x, boost.y, objects);
        Visual->position += boost * time;
        Visual->sprite.setPosition(Visual->position.x + Visual->size.x / 2, Visual->position.y + Visual->size.y / 2);
        if (health <= 0) {
            alive = false;
        }
    }
}
