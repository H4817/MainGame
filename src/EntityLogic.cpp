#include "EntityLogic.h"


EntityLogic::EntityLogic(String Name, EntityVisual * visual) {
    *Visual = *visual;
    name = Name;
    moveTimer = 0;
    speed = 0;
    health = 100;
    boost = {0, 0};
    alive = true;
    isMove = false;
}

FloatRect EntityLogic::getRect(EntityVisual & visual) {
    return FloatRect(visual.position.x, visual.position.y, visual.size.x, visual.size.y);
}