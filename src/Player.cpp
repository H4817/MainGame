#include "Player.h"


void getPlayerCoordinateForView(Vector2f position, PlayerProperties &playerProperties);


Player::Player(Image &image, MapObjects &objects, Level &lev, Vector2f Position, Vector2i Size, String Name) : Entity(
        image, Position, Size,
        Name) {
    // m_shipTexture.loadFromFile("IMG/8888.png");
    //m_shipWithThrust.setTexture(m_shipTexture);
    // m_shipWithoutThrust = sprite;
    health = playerProperties.HEALTH;
    playerScore = 0;
    state = STAY;
    objects.obj = lev.GetAllObjects();
    if (name == "player") {
        sprite.setPosition(size.x, size.y);
        sprite.setOrigin(ImageSize.x / 2, ImageSize.y / 2);
    }
}

void Player::control(const float &time) {
    SetRightPosition(position);
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {

        //  sprite = m_shipWithThrust;
        state = MOVE;
        distance = sqrt((m_temp.x - position.x) * (m_temp.x - position.x) + (m_temp.y - position.y) * (m_temp.y -
                                                                                                       position.y));
        if (distance > 2 ) {
            velocity += {static_cast<float>(0.003 * time * (m_temp.x - position.x) / distance),
                         static_cast<float>(0.003 * time * (m_temp.y - position.y) / distance)};

        }
    }
    else if (state == MOVE || state == SLIDE) {
        // sprite = m_shipWithoutThrust;
        state = SLIDE;
        velocity.x *= 0.99;
        velocity.y *= 0.99;
    }
    //else if (velocity.x == 0 && velocity.y == 0) {
    //  state == STAY;
    //}
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
    control(time);
    /*if (state == STAY || state == SLIDE) {
        sprite = m_shipWithoutThrust;
    }
    else {
        sprite = m_shipWithThrust;
    }*/
    position.x += boost.x * time;
    checkCollisionWithMap(boost.x, 0, objects);
    position.y += boost.y * time;
    playerProperties.position = position;
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
        getPlayerCoordinateForView(position, playerProperties);
    }
}





























/*
 *
 *
        if (distance > 2 && counter < 160) {
            ++counter;
            velocity += {static_cast<float>(0.003 * time * (m_temp.x - position.x) / distance),
                         static_cast<float>(0.003 * time * (m_temp.y - position.y) / distance)};

            cout << "first " << counter << endl;
        }
        else if (counter < 240) {
            ++counter;
            velocity -= {static_cast<float>(0.003 * time * (m_temp.x - position.x) / distance),
                         static_cast<float>(0.003 * time * (m_temp.y - position.y) / distance)};
            cout << "second " << counter << endl;
        }
        else if (counter == 240) {
            counter = 0;
        }
 */
