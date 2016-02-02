#include "shield.h"

Shield::Shield() {
    texture1.loadFromFile("IMG/shieldR.png");
    shield.setTexture(texture1);
}

void Shield::draw(RenderWindow & window, Vector2f position) {
    shield.setPosition(position.x - 25, position.y - 25);
    window.draw(shield);
}
