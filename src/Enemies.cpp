#include "Enemies.h"

CEasyEnemy::CEasyEnemy(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size, Vector2f &temp,
                       String Name) : Entity(image, Position, Size, Name) {
    m_isAggro = false;
    m_playerCoordinates = &objects.playerPosition;
    m_frameCounter = 0;
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    boost = {position.x, position.y};
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
    m_explosionTexture.loadFromFile("IMG/Exp_type_B1.png");
    m_shieldRewardTexture.loadFromFile("IMG/shieldReward.png");
    m_healthRewardTexture.loadFromFile("IMG/healthReward.png");
}

void CEasyEnemy::CreateNewReward() {
    sprite.setTextureRect(IntRect(0, 0, 40, 37));
    if (rand() % 2 == 0) {
        sprite.setTexture(m_healthRewardTexture);
        sprite.setTextureRect(IntRect(0, 0, 28, 24));
        name = "HealthReward";
    }
    else {
        sprite.setTexture(m_shieldRewardTexture);
        sprite.setTextureRect(IntRect(0, 0, 28, 24));
        name = "ShieldReward";
    }
}

void CEasyEnemy::ExplosionAnimation(const float &time) {
    m_frameCounter += 0.054 * time;
    sprite.setTexture(m_explosionTexture);
    sprite.setTextureRect(IntRect(96 * int(m_frameCounter), 0, 96, 96));
}

void CEasyEnemy::Update(float time, MapObjects &objects) {
    SetRightPosition(position);
    if (name == "easyEnemy" || name == "mediumEnemy" || name == "strongEnemy") {
        distance = sqrt((m_playerCoordinates->x - position.x) * (m_playerCoordinates->x - position.x) +
                        (m_playerCoordinates->y - position.y) * (m_playerCoordinates->y - position.y));
        if (!m_isAggro && (distance < 800 || enemyHealth != MAX_HEALTH)) {
            m_isAggro = true;
        }
        else if (m_isAggro) {
            m_rotation = static_cast<float>(
                    (atan2(m_playerCoordinates->y - position.y, m_playerCoordinates->x - position.x)) *
                    parameters.ANGLE / M_PI);
            if (distance > 250) {
                velocity += {static_cast<float>(ACCELERATION * time * (m_playerCoordinates->x - position.x) / distance),
                             static_cast<float>(ACCELERATION * time * (m_playerCoordinates->y - position.y) /
                                                distance)};
            }
            else {
                velocity.x *= DECELERATION;
                velocity.y *= DECELERATION;
            }
            sprite.setRotation(m_rotation);
            position.x += velocity.x;
            position.y += velocity.y;
            sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
        }
        if (enemyHealth <= 0) {
            name = "explosion";
        }
    }
    else if (name == "explosion") {
        ExplosionAnimation(time);
        if (m_frameCounter > 64) {
            CreateNewReward();
        }
    }
}

CMediumEnemy::CMediumEnemy(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size,
                           Vector2f &temp, String Name) : CEasyEnemy(image, objects, Position, Size, temp, Name) {
    enemyHealth = static_cast<int>(enemiesHandler.mediumEnemy.health);
    m_isAggro = false;
    m_playerCoordinates = &objects.playerPosition;
    m_frameCounter = 0;
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    boost = {position.x, position.y};
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
}

void CMediumEnemy::Update(float time, MapObjects &objects) {
    CEasyEnemy::Update(time, objects);
}

void CMediumEnemy::CreateNewReward() {
    CEasyEnemy::CreateNewReward();
}

void CMediumEnemy::ExplosionAnimation(const float &time) {
    CEasyEnemy::ExplosionAnimation(time);
}

CStrongEnemy::CStrongEnemy(Image &image, MapObjects &objects, Vector2f Position, Vector2i Size,
                           Vector2f &temp, String Name) : CMediumEnemy(image, objects, Position, Size, temp,
                                                                       Name) {
    enemyHealth = static_cast<int>(enemiesHandler.hardEnemy.health);
    m_isAggro = false;
    m_playerCoordinates = &objects.playerPosition;
    m_frameCounter = 0;
    sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    boost = {position.x, position.y};
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
}

