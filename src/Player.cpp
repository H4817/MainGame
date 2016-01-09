#include "Player.h"


void getPlayerCoordinateForView(Vector2f position);


Player::Player(MapObjects & objects, Level &lev, String Name, std::list<EntityVisual*> visual) : EntityLogic(Name, Visual) {
    playerScore = 0;
    state = stay;
    objects.obj = lev.GetAllObjects();
    if (name == "Player") {
        Visual->sprite.setPosition(Visual->size.x, Visual->size.y);
    }
}

void Player::control() {
    bool pressBut = false;
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        state = left;
        speed = playerProperties.SPEED;
        pressBut = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        state = right;
        speed = playerProperties.SPEED;
        pressBut = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        if (pressBut) {
            if (state == right) {
                state = rightUp;
                speed = playerProperties.SPEED;
            }
            if (state == left) {
                state = leftUp;
                speed = playerProperties.SPEED;
            }
        }
        else {
            state = up;
            speed = playerProperties.SPEED;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        if (pressBut) {
            if (state == right) {
                state = rightDown;
                speed = playerProperties.SPEED;
            }
            if (state == left) {
                state = leftDown;
                speed = playerProperties.SPEED;
            }
        }
        else {
            state = down;
            speed = playerProperties.SPEED;
        }
    }
}

void Player::rotation_GG(Vector2f pos) {
    float dX = pos.x - Visual->position.x;
    float dY = pos.y - Visual->position.y;
    rotation = (atan2(dY, dX)) * parameters.ANGLE / M_PI;
}

void Player::checkCollisionWithMap(float Dx, float Dy, MapObjects & objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect(*Visual).intersects(objects.obj[i].rect)) {
            if (objects.obj[i].name == "solid") {
                if (Dy > 0) {
                    Visual->position.y = objects.obj[i].rect.top - Visual->size.y;
                    boost.y = 0;
                }
                if (Dy < 0) {
                    Visual->position.y = objects.obj[i].rect.top + objects.obj[i].rect.height;
                    boost.y = 0;
                }
                if (Dx > 0) {
                    Visual->position.x = objects.obj[i].rect.left - Visual->size.x;
                }
                if (Dx < 0) {
                    Visual->position.x = objects.obj[i].rect.left + objects.obj[i].rect.width;
                }
            }
        }
    }
}

void Player::update(float time, MapObjects & objects, std::list<EntityVisual*> & visual) {
    Visual->sprite.setRotation(rotation);
    control();
    switch (state) {
        case right:
            boost = {speed, 0};
            break;
        case rightUp:
            boost = {speed, -speed};
            break;
        case rightDown:
            boost = {speed, speed};
            break;
        case left:
            boost = {-speed, 0};
            break;
        case leftUp:
            boost = {-speed, -speed};
            break;
        case leftDown:
            boost = {-speed, speed};
            break;
        case up:
            boost = {0, -speed};
            break;
        case down:
            boost = {0, speed};
            break;
        case stay:
            break;
    }
    Visual->position.x += boost.x * time;
    checkCollisionWithMap(boost.x, 0, objects);
    Visual->position.y += boost.y * time;
    checkCollisionWithMap(0, boost.y, objects);
    Visual->sprite.setPosition(Visual->position.x + Visual->size.x / 2, Visual->position.y + Visual->size.y / 2);

    if (health <= 0) {
        alive = false;
    }
    if (!isMove) {
        speed = 0;
    }
    if (alive) {
        getPlayerCoordinateForView(Visual->position);
    }
}
