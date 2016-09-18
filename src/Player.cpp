#include "Player.h"

void getPlayerCoordinateForView(Vector2f position);

Player::Player(Image &image, Vector2f Position, Vector2i Size, String Name) : Entity(
        image, Position, Size, Name) {
    withoutThrust.loadFromFile("IMG/888.png");
    withThrust.loadFromFile("IMG/8888.png");
    shield = static_cast<int>(MAX_SHIELD);
    health = static_cast<int>(MAX_HP);
    state = STAY;
    amountOfMissiles = 20;
    currentWeapon = BULLET;
    if (name == "player") {
        sprite.setPosition(size.x, size.y);
        sprite.setOrigin(Size.x / 2, Size.y / 2);
    }
}

void Player::SetAmountOfMissile(size_t amount) {
    amountOfMissiles = amount;
}

size_t Player::GetAmountOfMissile() {
    return amountOfMissiles;
}

size_t Player::GetCurrentWeapon() {
    return currentWeapon;
}

void Player::SetCurrentWeapon(size_t weaponNumber) {
    currentWeapon = static_cast<CurrentWeapon>(weaponNumber);
}

int Player::GetState() {
    return state;
}

void Player::control(const float &time) {
    SetPositionOnAnotherSide(position);
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        state = MOVE;
        distance = sqrt((m_temp.x - position.x) * (m_temp.x - position.x) + (m_temp.y - position.y) * (m_temp.y -
                                                                                                       position.y));
        if (distance > 2) {
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

void Player::ProcessState() {
    if (state == MOVE) {
//        sprite.setTexture(withThrust);
    }
    else {
//        sprite.setTexture(withoutThrust);
    }
}

void Player::Update(float time, MapObjects &objects) {
    sprite.setRotation(rotation);
    control(time);
    position.x += boost.x * time;
    position.y += boost.y * time;
    objects.playerPosition = position;
    objects.playerRotation = rotation;
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    if (health <= 0) {
        alive = false;
    }
    else {
        getPlayerCoordinateForView(position);
    }
    ProcessState();
}

int Player::GetShield() const {
    return shield;
}

void Player::SetShield(int shield) {
    Player::shield = shield;
}

int Player::GetHealth() const {
    return health;
}

void Player::SetHealth(int health) {
    Player::health = health;
}

const size_t Player::GetMAX_HP() const {
    return MAX_HP;
}

const size_t Player::GetMAX_SHIELD() const {
    return MAX_SHIELD;
}
