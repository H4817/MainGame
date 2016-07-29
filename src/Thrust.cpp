#include "Thrust.h"

Thrust::Thrust() {
    texture1.loadFromFile("IMG/thrust_green22.png");
    thrust.setTexture(texture1);
    thrust.setOrigin(43/2, 43/2);
    frameCounter = 0;
}

void Thrust::Draw(RenderWindow &window, Vector2f &position, float &rotation) {
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 800;
    if (frameCounter > 24) {
        frameCounter = 0;
    }
    else {
        thrust.setTextureRect(IntRect(0, 42.666 * int(frameCounter), 43, 43));
        frameCounter += 0.03 * time;
    }
    thrust.setPosition(position.x + 45, position.y + 56.25);
    thrust.setRotation(rotation);
    window.draw(thrust);
}