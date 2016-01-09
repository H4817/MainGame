#include "Bullet.h"



Bullet::Bullet(MapObjects & objects, Level &lvl, Vector2f temp, String Name, std::list<EntityVisual*> visual) : EntityLogic(Name, Visual) {//////////
    objects.obj = lvl.GetObjects("solid");
    speed = 0.1;
    EntityLogic::temp = temp;
    boost = {Visual->position.x, Visual->position.y};
    rotation = (atan2(temp.y - Visual->position.y, temp.x - Visual->position.x)) * parameters.ANGLE / M_PI;
}

void Bullet::update(float time, MapObjects & objects, std::list<EntityVisual*> & visual) {
    Visual->position += (temp - boost) * speed;

    if (Visual->position.x <= 0)
        Visual->position.x = 1;

    if (Visual->position.y <= 0)
        Visual->position.y = 1;

    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect(*Visual).intersects(objects.obj[i].rect)) {
            alive = false;
        }
    }
    Visual->sprite.setRotation(rotation);
    Visual->sprite.setPosition(Visual->position.x + Visual->size.x / 2, Visual->position.y + Visual->size.y / 2);
}
