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

void Entity::ReduceSpeed() {
    velocity.x *= 0.2;
    velocity.y *= 0.2;
}

bool Entity::IsCharacter() {
    return (name == "player" || name == "easyEnemy" || name == "mediumEnemy" || name == "strongEnemy");
}

void Entity::SetPositionOnAnotherSide(Vector2f &position) {
    if (position.x < 0) {
        position.x = parameters.MAP_SIZE.first;
        if (IsCharacter())
            ReduceSpeed();
    }
    if (position.y < 0) {
        position.y = parameters.MAP_SIZE.second;
        if (IsCharacter())
            ReduceSpeed();
    }

    if (position.x > parameters.MAP_SIZE.first) {
        position.x = 0;
        if (IsCharacter())
            ReduceSpeed();
    }
    if (position.y > parameters.MAP_SIZE.second) {
        position.y = 0;
        if (IsCharacter())
            ReduceSpeed();
    }
}


