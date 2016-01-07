#include "EntityLogic.h"
#include "EntityVisual.h"


EntityLogic::EntityLogic(String Name) {
    EntityVisual * visual;
    name = Name;
    moveTimer = 0;
    speed = 0;
    health = 100;
    boost = {0, 0};
    alive = true;
    isMove = false;
}

FloatRect EntityLogic::getRect() {
    return FloatRect(position.x, position.y, size.x, size.y);
}