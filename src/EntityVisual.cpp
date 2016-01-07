#include "EntityVisual.h"


EntityVisual::EntityVisual(Image &image, Vector2f Position, Vector2i Size) {
    position = Position;
    size = Size;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(size.x / 2, size.y / 2);
}

FloatRect EntityVisual::getRect() {
    return FloatRect(position.x, position.y, size.x, size.y);
}