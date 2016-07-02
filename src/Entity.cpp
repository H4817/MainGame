#include "Entity.h"

Entity::Entity(Image &image, Vector2f Position, Vector2i Size, String Name) {
    position = Position;
    size = Size;
    name = Name;
    speed = 0;
    boost = {0, 0};
    alive = true;
    isMove = false;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(size.x / 2, size.y / 2);
}

FloatRect Entity::RetRect() {
    return FloatRect(position.x, position.y, size.x, size.y);
}

void Entity::SetRightPosition(Vector2f &position) {
    if (position.x <= 20) {
        position.x = 20;
        velocity.x = 0;
    }
    if (position.y <= 10) {
        position.y = 10;
        velocity.y = 0;
    }

    if (position.x >= parameters.MAP_SIZE.first) {
        position.x = parameters.MAP_SIZE.first;
        velocity.x = 0;
    }
    if (position.y >= parameters.MAP_SIZE.second) {
        velocity.y = 0;
        position.y = parameters.MAP_SIZE.second;
    }
}

/*bool Entity::isCollide(Entity *a,Entity *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}*/

