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
    enemyBarBlack.setFillColor(Color(0, 0, 0));
    playerBarBlackHP.setRotation(180);
    playerBarBlackHP.setFillColor(Color(0, 0, 0));
    playerBarBlackShield.setRotation(180);
    playerBarBlackShield.setFillColor(Color(0, 0, 0));
}

void Bar::UpdateEnemy(int &Health) {
    healthBarOffset = {static_cast<float>((maxHealthEnemy - Health)+1.2), 10};
    if ((Health > 0) && (Health < maxHealthEnemy)) {
        enemyBarBlack.setSize(healthBarOffset);
    }
}

void Bar::UpdateProtagonist(int &Health, int &Shield) {
    if ((Health > 0) && (Health < maxHealthPlayer)) {
        healthBarOffset = {(maxHealthPlayer - Health)-6, 10};
        playerBarBlackHP.setSize(healthBarOffset);
    }
    if ((Shield > 0) && (Shield < maxShieldPlayer)) {
        shieldBarOffset = {(maxShieldPlayer - Shield)-6, 10};
        playerBarBlackShield.setSize(shieldBarOffset);
    }
}

void Bar::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    playerBarHealth.setPosition((center.x - size.x  / halfScreen), center.y - size.y / halfScreen + 15);
    playerBarShield.setPosition((center.x - size.x  / halfScreen), center.y - size.y / halfScreen + 45);
    playerBarBlackHP.setPosition((center.x - size.x  / halfScreen) + 200, center.y - size.y / halfScreen + 30);
    playerBarBlackShield.setPosition((center.x - size.x  / halfScreen) + 200, center.y - size.y / halfScreen + 60);
    enemyBarBlack.setPosition((center.x - size.x  / halfScreen) +  950, (center.y - size.y / halfScreen) + 1035);
    enemyBar.setPosition((center.x - size.x  / halfScreen) + 750, (center.y - size.y / halfScreen) + 1020);

    window.draw(playerBarHealth);
    window.draw(playerBarShield);
    window.draw(enemyBar);
    window.draw(enemyBarBlack);
    window.draw(playerBarBlackHP);
    window.draw(playerBarBlackShield);
}
