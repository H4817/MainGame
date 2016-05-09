#include "Thrust.h"

Thrust::Thrust() {
    texture1.loadFromFile("IMG/thrust_green22.png");
    thrust.setTexture(texture1);
}

void Thrust::Draw(RenderWindow &window, Vector2f &position, float &rotation) {
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 800;
    if (frameCounter > 24) {
        frameCounter -= 24;
    }
    else {
        thrust.setTextureRect(IntRect(42.66666 * int(frameCounter), 43, 36, 43));
        frameCounter += 0.005 * time;
    }
    thrust.setPosition(position.x, position.y);
    thrust.setRotation(rotation);
    window.draw(thrust);
}