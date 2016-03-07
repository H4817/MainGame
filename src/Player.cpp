#include "Player.h"


void getPlayerCoordinateForView(Vector2f position, PlayerProperties &playerProperties);


Player::Player(Image &image, MapObjects &objects, Level &lev, Vector2f Position, Vector2i Size, String Name) : Entity(
        image, Position, Size,
        Name) {
    playerScore = 0;
    state = stay;
    objects.obj = lev.GetAllObjects();
    if (name == "player") {
        sprite.setPosition(size.x, size.y);
        sprite.setOrigin(ImageSize.x / 2, ImageSize.y / 2);
    }
}

void Player::control() {
    bool pressBut = false;
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        state = left;
        speed = playerProperties.SPEED;
        pressBut = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        state = right;
        speed = playerProperties.SPEED;
        pressBut = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
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
    if (Keyboard::isKeyPressed(Keyboard::S)) {
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
    isMOVE = false;
}

void Player::rotation_GG(Vector2f pos) {
    float dX = pos.x - position.x;
    float dY = pos.y - position.y;
    rotation = (atan2(dY, dX)) * parameters.ANGLE / M_PI;
}

void Player::checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (getRect().intersects(objects.obj[i].rect)) {
            if (objects.obj[i].name == "solid") {
                if (Dy > 0) {
                    position.y = objects.obj[i].rect.top - size.y;
                    boost.y = 0;
                }
                if (Dy < 0) {
                    position.y = objects.obj[i].rect.top + objects.obj[i].rect.height;
                    boost.y = 0;
                }
                if (Dx > 0) {
                    position.x = objects.obj[i].rect.left - size.x;
                }
                if (Dx < 0) {
                    position.x = objects.obj[i].rect.left + objects.obj[i].rect.width;
                }
            }
        }
    }
}

void Player::update(float time, MapObjects &objects) {
    sprite.setRotation(rotation);
    control();
    switch (state) {
        case right:
            boost = {speed, 0};
            isMOVE = true;
            break;
        case rightUp:
            boost = {speed, -speed};
            isMOVE = true;
            break;
        case rightDown:
            boost = {speed, speed};
            isMOVE = true;
            break;
        case left:
            boost = {-speed, 0};
            isMOVE = true;
            break;
        case leftUp:
            boost = {-speed, -speed};
            isMOVE = true;
            break;
        case leftDown:
            boost = {-speed, speed};
            isMOVE = true;
            break;
        case up:
            boost = {0, -speed};
            isMOVE = true;
            break;
        case down:
            boost = {0, speed};
            isMOVE = true;
            break;
        case stay:
            isMOVE = false;
            break;
    }
    position.x += boost.x * time;
    checkCollisionWithMap(boost.x, 0, objects);
    position.y += boost.y * time;
    checkCollisionWithMap(0, boost.y, objects);
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);

    if (health <= 0) {
        alive = false;
    }
    if (!isMove) {
        speed = 0;
    }
    if (alive) {
        getPlayerCoordinateForView(position, playerProperties);
    }
}
