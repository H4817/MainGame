#include "Enemy.h"



Enemy::Enemy(Image &image, Level &lvl, Vector2f Position, Vector2i Size, String Name) :Entity(image, Position, Size, Name) {
		g_objects.obj = lvl.GetObjects("solid");
		if (name == "easyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
			sprite.rotate(g_parameters.ANGLE);
			boost.x = -g_easyEnemy.SPEED;
		}
	}

	void Enemy::checkCollisionWithMap(float Dx, float Dy) {
		for (int i = 0; i < g_objects.obj.size(); i++) {
			if (getRect().intersects(g_objects.obj[i].rect)) {
				if (g_objects.obj[i].name == "solid") {
					if (Dy > 0) {
						position.y = g_objects.obj[i].rect.top - size.y;
						boost.y = -g_easyEnemy.SPEED;
					}
					if (Dy < 0) {
						position.y = g_objects.obj[i].rect.top + g_objects.obj[i].rect.height;
						boost.y = g_easyEnemy.SPEED;
					}
					if (Dx > 0) {
						position.x = g_objects.obj[i].rect.left - size.x;
						boost.x = -g_easyEnemy.SPEED;
					}
					if (Dx < 0) {
						position.x = g_objects.obj[i].rect.left + g_objects.obj[i].rect.width;
						boost.x = g_easyEnemy.SPEED;
					}
				}
			}
		}
	}

	void Enemy::update(float time) {
		if (name == "easyEnemy") {
			checkCollisionWithMap(boost.x, boost.y);
			position.x += boost.x*time;
			position.y += boost.y*time;
			sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
			if (health <= 0) {
				alive = false;
			}
		}
	}
