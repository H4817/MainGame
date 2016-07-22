#include <stdlib.h>
#include "Asteroid.h"

Asteroid::Asteroid(Image &image, Vector2f Position, Vector2i Size, String Name) : Entity(image,
                                                                                         Position, Size,
                                                                                         Name) {
    velocity = {rand() % 8 - 4, rand() % 8 - 4};
    health = 200;
    sprite.setOrigin(IMAGE_SIZE.x / 2, IMAGE_SIZE.y / 2);
    m_explosionTexture.loadFromFile("IMG/Exp_type_A1.png");
}

void Asteroid::Animation(float time) {

}

void Asteroid::Update(float time, MapObjects &objects) {
    if (health <= 0) {
        alive = false;
    }
    SetRightPosition(position);
//    Animation(time);
    position += velocity;
    sprite.setPosition(position);
}
