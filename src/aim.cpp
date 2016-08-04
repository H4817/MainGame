#include "aim.h"


Aim::Aim() {
    texture1.loadFromFile("IMG/cursor0.png");
    aim.setTexture(texture1);
    aim.setOrigin(25, 25);
}

void Aim::Draw(RenderWindow &window) {
    Vector2i pixelPos = Mouse::getPosition(window);
    position = window.mapPixelToCoords(pixelPos);
    aim.setPosition(position);
    window.draw(aim);
}