#include "Player.h"


void getPlayerCoordinateForView(Vector2f position);


Player::Player(Image &image, Level &lev, Vector2f Position, Vector2i Size, String Name) : Entity(image, Position, Size,
                                                                                                 Name) {
    playerScore = 0;
    state = stay;
    isSelect = false;
    g_objects.obj = lev.GetAllObjects();
    if (name == "Player") {
        sprite.setPosition(size.x, size.y);
    }
}

void Player::control() {
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

void Player::rotation_GG(Vector2f pos) {
    float dX = pos.x - position.x;
    float dY = pos.y - position.y;
    rotation = (atan2(dY, dX)) * g_parameters.ANGLE / M_PI;
}

void Player::checkCollisionWithMap(float Dx, float Dy) {
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

void Player::update(float time) {
    sprite.setRotation(rotation);
    control();
    switch (state) {
        case right:
            boost.x = speed;
            boost.y = 0;
            break;
        case rightUp:
            boost.x = speed;
            boost.y = -speed;
            break;
        case rightDown:
            boost.x = speed;
            boost.y = speed;
            break;
        case left:
            boost.x = -speed;
            boost.y = 0;
            break;
        case leftUp:
            boost.x = -speed;
            boost.y = -speed;
            break;
        case leftDown:
            boost.x = -speed;
            boost.y = speed;
            break;
        case up:
            boost.x = 0;
            boost.y = -speed;
            break;
        case down:
            boost.x = 0;
            boost.y = speed;
            break;
        case stay:
            break;
    }
    position.x += boost.x * time;
    checkCollisionWithMap(boost.x, 0);
    position.y += boost.y * time;
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
