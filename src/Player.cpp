#include "Player.h"

void getPlayerCoordinateForView(Vector2f position);

Player::Player(Image &image, Vector2f Position, Vector2i Size, String Name) : Entity(
        image, Position, Size, Name) {
    health = static_cast<int>(MAX_HP);
    state = STAY;
    if (name == "player") {
        sprite.setPosition(size.x, size.y);
        sprite.setOrigin(ImageSize.x / 2, ImageSize.y / 2);
    }
}

void Player::control(const float &time) {
    SetRightPosition(position);
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        state = MOVE;
        distance = sqrt((m_temp.x - position.x) * (m_temp.x - position.x) + (m_temp.y - position.y) * (m_temp.y -
                                                                                                       position.y));
        if (distance > 2 ) {
            velocity += {static_cast<float>(ACCELERATION * time * (m_temp.x - position.x) / distance),
                         static_cast<float>(ACCELERATION * time * (m_temp.y - position.y) / distance)};

        }
    }
    else if (state == MOVE || state == SLIDE) {
        state = SLIDE;
        velocity.x *= DECELERATION;
        velocity.y *= DECELERATION;
    }
    position.x += velocity.x;
    position.y += velocity.y;
}

void Player::rotation_GG(Vector2f pos) {
    float dX = pos.x - position.x;
    float dY = pos.y - position.y;
    m_temp = pos;
    rotation = static_cast<float>((atan2(dY, dX)) * parameters.ANGLE / M_PI);
}

void Player::checkCollisionWithMap(float Dx, float Dy, MapObjects &objects) {
    for (int i = 0; i < objects.obj.size(); i++) {
        if (RetRect().intersects(objects.obj[i].rect)) {
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

void Player::Update(float time, MapObjects &objects) {
    sprite.setRotation(rotation);
    control(time);
    position.x += boost.x * time;
    checkCollisionWithMap(boost.x, 0, objects);
    position.y += boost.y * time;
    objects.playerPosition = position;
    checkCollisionWithMap(0, boost.y, objects);
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
