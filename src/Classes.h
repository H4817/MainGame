#pragma once

#include <SFML/Graphics.hpp>
#include "level.h"
#include <vector>
#include <list>

using namespace sf;

void getPlayerCoordinateForView(Vector2f position);

struct Parameters {
	const unsigned WINDOW_SIZE_X = 1680;
	const unsigned WINDOW_SIZE_Y = 1050;
	const unsigned ANGLE = 180;
};

Parameters g_parameters;

struct PlayerBullet {
	const Vector2i SIZE = {100, 14};
	const unsigned DAMAGE = 10;
};

PlayerBullet g_playerBullet;

struct EasyEnemy {
	const Vector2i SIZE = {74, 67};
	const unsigned DAMAGE = 1;
	const float SPEED = 0.1;
};

EasyEnemy g_easyEnemy;

struct PlayerProperties {
	const Vector2i SIZE = {147, 125};
	const int HEALTH = 100;
	const float SPEED = 0.2;
};

PlayerProperties g_playerProperties;

struct MapObjects {
	std::vector<Object> obj;
};

MapObjects g_objects;

class Entity {
public:
	float speed, moveTimer;
	Vector2f boost;
	Vector2f position;
	int health;
	Vector2i size;
	bool alive, isMove, isSelect;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, Vector2f Position, Vector2i Size, String Name) {
		position = Position; size = Size; name = Name; moveTimer = 0;
		speed = 0; health = 100; boost.x = 0; boost.y = 0;
		alive = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(size.x / 2, size.y / 2);
	}
	FloatRect getRect() {
		return FloatRect(position.x, position.y, size.x, size.y);
	}
	virtual void update(float time) = 0;
};


class Player :public Entity {
public:
	enum { left, right, up, down, leftUp, rightUp, leftDown, rightDown, stay } state;
	float rotation;
	int playerScore;
	Player(Image &image, Level &lev, Vector2f Position, Vector2i Size, String Name) :Entity(image, Position, Size, Name) {
		playerScore = 0;
		state = stay;
		isSelect = false;
		g_objects.obj = lev.GetAllObjects();
		if (name == "Player") {
			sprite.setPosition(size.x, size.y);
		}
	}

	void control() {
		bool pressBut = false;
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = g_playerProperties.SPEED;
			pressBut = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = g_playerProperties.SPEED;
			pressBut = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (pressBut) {
				if (state == right) {
					state = rightUp;
					speed = g_playerProperties.SPEED;
				}
				if (state == left) {
					state = leftUp;
					speed = g_playerProperties.SPEED;
				}
			}
			else {
				state = up;
				speed = g_playerProperties.SPEED;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (pressBut) {
				if (state == right) {
					state = rightDown;
					speed = g_playerProperties.SPEED;
				}
				if (state == left) {
					state = leftDown;
					speed = g_playerProperties.SPEED;
				}
			}
			else {
				state = down;
				speed = g_playerProperties.SPEED;
			}
		}
	}
	void rotation_GG(Vector2f pos) {
		float dX = pos.x - position.x;
		float dY = pos.y - position.y;
		rotation = (atan2(dY, dX)) * g_parameters.ANGLE / M_PI;
	}
	void checkCollisionWithMap(float Dx, float Dy) {
		for (int i = 0; i < g_objects.obj.size(); i++) {
			if (getRect().intersects(g_objects.obj[i].rect)) {
				if (g_objects.obj[i].name == "solid") {
					if (Dy > 0) {
						position.y = g_objects.obj[i].rect.top - size.y;
						boost.y = 0;
					}
					if (Dy < 0) {
						position.y = g_objects.obj[i].rect.top + g_objects.obj[i].rect.height;
						boost.y = 0;
					}
					if (Dx > 0) {
						position.x = g_objects.obj[i].rect.left - size.x;
					}
					if (Dx < 0) {
						position.x = g_objects.obj[i].rect.left + g_objects.obj[i].rect.width;
					}
				}
			}
		}
	}

	void update(float time)	{
		sprite.setRotation(rotation);
		control();
		switch (state) {
			case right: boost.x = speed; boost.y = 0; break;
			case rightUp: boost.x = speed; boost.y = -speed; break;
			case rightDown: boost.x = speed; boost.y = speed; break;
			case left: boost.x = -speed; boost.y = 0; break;
			case leftUp: boost.x = -speed; boost.y = -speed; break;
			case leftDown: boost.x = -speed; boost.y = speed; break;
			case up: boost.x = 0; boost.y = -speed; break;
			case down: boost.x = 0; boost.y = speed; break;
			case stay: break;
		}
		position.x += boost.x*time;
		checkCollisionWithMap(boost.x, 0);
		position.y += boost.y*time;
		checkCollisionWithMap(0, boost.y);
		sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);

		if (health <= 0) {
			alive = false;
		}
		if (!isMove) {
			speed = 0;
		}
		if (alive) {
			getPlayerCoordinateForView(position);
		}
	}
};


class Enemy :public Entity {
public:
	Enemy(Image &image, Level &lvl, Vector2f Position, Vector2i Size, String Name) :Entity(image, Position, Size, Name) {
		g_objects.obj = lvl.GetObjects("solid");
		if (name == "easyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
			sprite.rotate(g_parameters.ANGLE);
			boost.x = -g_easyEnemy.SPEED;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy) {
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

	void update(float time) {
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
};


class Bullet :public Entity {
public:
	int direction;
	float tempy, tempx, rotation, Dx, Dy;
	Bullet(Image &image, Level &lvl, Vector2f Position, Vector2i Size, Vector2f temp, String Name) :Entity(image, Position, Size, Name) {
		g_objects.obj = lvl.GetObjects("solid");
		position = Position;
		speed = 0.1;
		tempx = temp.x;
		tempy = temp.y;
		size = Size;
		alive = true;
		boost.x = position.x;
		boost.y = position.y;
		alive = true;
		Dx = tempx - position.x;
		Dy = tempy - position.y;
		rotation = (atan2(Dy, Dx)) * g_parameters.ANGLE / M_PI;
	}

	void update(float time) {
		position.x += speed * (tempx - boost.x);
		position.y += speed * (tempy - boost.y);

		if (position.x <= 0)
			position.x = 1;

		if (position.y <= 0)
			position.y = 1;

		for (int i = 0; i < g_objects.obj.size(); i++) {
			if (getRect().intersects(g_objects.obj[i].rect)) {
				alive = false;
			}
		}
		sprite.setRotation(rotation);
		sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
	}
};