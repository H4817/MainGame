#include "Bar.h"

Bar::Bar() {
    texture1.loadFromFile("IMG/EnemyBar.png");
    playerBarHealth.setTexture(texture1);

    texture2.loadFromFile("IMG/BlueBar.png");
    playerBarShield.setTexture(texture2);

    entitiesBar.loadFromFile("IMG/EnemyBar.png");
    entitiesTexture.loadFromImage(entitiesBar);
    enemyBar.setTexture(entitiesTexture);
    enemyBarBlack.setRotation(180);
    enemyBarBlack.setFillColor(sf::Color(0, 0, 0));
    playerBarBlackHP.setRotation(180);
    playerBarBlackHP.setFillColor(sf::Color(0, 0, 0));
    playerBarBlackShield.setRotation(180);
    playerBarBlackShield.setFillColor(sf::Color(0, 0, 0));
}

void Bar::UpdateEnemy(size_t Health) {
    if ((Health > 0) && (Health < enemiesHandler.easyEnemy.health)) {
        healthBarOffset = {static_cast<float>((enemiesHandler.easyEnemy.health - Health)), 10};
        enemyBarBlack.setSize(healthBarOffset);
    }
}

void Bar::UpdateProtagonist(size_t Health, size_t Shield) {
    if ((Health > 0) && (Health < playerProperties.HEALTH)) {
        healthBarOffset = {(playerProperties.HEALTH - Health) - 6, 10};
        playerBarBlackHP.setSize(healthBarOffset);
    }
    if ((Shield > 0) && (Shield < playerProperties.shield)) {
        shieldBarOffset = {(playerProperties.shield - Shield) - 6, 10};
        playerBarBlackShield.setSize(shieldBarOffset);
    }
}

void Bar::Draw(sf::RenderWindow &window) {
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    playerBarHealth.setPosition((center.x - size.x / 2), center.y - size.y / 2 + 15);
    playerBarShield.setPosition((center.x - size.x / 2), center.y - size.y / 2 + 45);
    playerBarBlackHP.setPosition((center.x - size.x / 2) + 200, center.y - size.y / 2 + 30);
    playerBarBlackShield.setPosition((center.x - size.x / 2) + 200, center.y - size.y / 2 + 60);
    enemyBarBlack.setPosition((center.x - size.x / 2) + 950, (center.y - size.y / 2) + 1035);
    enemyBar.setPosition((center.x - size.x / 2) + 750, (center.y - size.y / 2) + 1020);

    window.draw(playerBarHealth);
    window.draw(playerBarShield);
    window.draw(enemyBar);
    window.draw(enemyBarBlack);
    window.draw(playerBarBlackHP);
    window.draw(playerBarBlackShield);
}
