#include "shield.h"

Shield::Shield() {
    texture1.loadFromFile("IMG/shieldxx.png");
    shield.setTexture(texture1);
}

void Shield::Draw(sf::RenderWindow & window, sf::Vector2f position) {
    shield.setPosition(position.x - OFFSET.x, position.y - OFFSET.y);
    window.draw(shield);
}
