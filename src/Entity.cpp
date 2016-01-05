#pragma hdrstop
#include "Entity.h"
#pragma package(smart_init)


Entity::Entity(Image &image, Vector2f Position, Vector2i Size, String Name) {
		position = Position; size = Size; name = Name; moveTimer = 0;
		speed = 0; health = 100; boost.x = 0; boost.y = 0;
		alive = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(size.x / 2, size.y / 2);
}
FloatRect Entity::getRect() {
		return FloatRect(position.x, position.y, size.x, size.y);
}
