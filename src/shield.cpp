#include "shield.h"

Shield::Shield() {
    texture1.loadFromFile("IMG/shieldxx.png");
    shield.setTexture(texture1);
}

void Shield::Draw(RenderWindow & window, Vector2f position) {
    shield.setPosition(position.x - 35, position.y - 25);
    window.draw(shield);
}
