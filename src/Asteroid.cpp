#include <stdlib.h>
#include "Asteroid.h"

Asteroid::Asteroid(Image &image, Vector2f Position, Vector2i Size, String Name) : Entity(image,
                                                                                         Position, Size,
                                                                                         Name) {
    isExplosion = false;
    m_frameCounter = 0;
    velocity = {static_cast<float>(rand() % 8 - 4), static_cast<float>(rand() % 8 - 4)};
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
    m_explosionTexture.loadFromFile("IMG/Exp_type_B1.png");
}

void Asteroid::Animation(float time) {

    if (name == "explosion") {
        if (!isExplosion) {
            m_frameCounter = 0;
            isExplosion = true;
        }
        m_frameCounter += 0.054 * time;
        sprite.setTexture(m_explosionTexture);
        sprite.setTextureRect(IntRect(96 * int(m_frameCounter), 0, 96, 96));
        if (m_frameCounter > 64)
            alive = false;
    }

    else {
        m_frameCounter += 0.009 * time;
        sprite.setTextureRect(IntRect(64 * int(m_frameCounter), 0, 64, 64));
        if (m_frameCounter > 16)
            m_frameCounter = 0;
    }

}

void Asteroid::Update(float time, MapObjects &objects) {
    Animation(time);
    if (name != "explosion") {
        SetPositionOnAnotherSide(position);
        position += velocity;
        sprite.setPosition(position);
    }

}
