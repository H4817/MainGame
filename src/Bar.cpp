#include "Bar.h"

Bar::Bar() {
    texture1.loadFromFile("IMG/EnemyBar.png");
    playerBarHealth.setTexture(texture1);

    texture2.loadFromFile("IMG/BlueBar.png");
    playerBarShield.setTexture(texture2);

    entitiesBar.loadFromFile("IMG/EnemyBar.png");
    entitiesTexture.loadFromImage(entitiesBar);
    enemyBar.setTexture(entitiesTexture);
    blackRectangleForFillingEnemyHP.setRotation(180);
    blackRectangleForFillingEnemyHP.setFillColor(sf::Color(0, 0, 0));
    blackRectangleForFillingPlayerHP.setRotation(180);
    blackRectangleForFillingPlayerHP.setFillColor(sf::Color(0, 0, 0));
    blackRectangleForFillingPlayerShield.setRotation(180);
    blackRectangleForFillingPlayerShield.setFillColor(sf::Color(0, 0, 0));
}


void Bar::SetZeroSize(sf::RectangleShape &rectangleShape) {
    rectangleShape.setSize({BAR_WIDTH, Y_OFFSET});
}

void Bar::UpdateEnemy(size_t Health, const string &name) {
    if (name == "easyEnemy") {
        if ((Health > 0) && (Health <= enemiesHandler.easyEnemy.health)) {
            healthBarOffset = {
                    (BAR_WIDTH * (enemiesHandler.easyEnemy.health - Health) / enemiesHandler.easyEnemy.health),
                    Y_OFFSET};
            blackRectangleForFillingEnemyHP.setSize(healthBarOffset);
        }
        else {
            SetZeroSize(blackRectangleForFillingEnemyHP);
        }
    }
    else if (name == "mediumEnemy") {
        if ((Health > 0) && (Health <= enemiesHandler.mediumEnemy.health)) {
            healthBarOffset = {
                    (BAR_WIDTH * (enemiesHandler.mediumEnemy.health - Health) / enemiesHandler.mediumEnemy.health),
                    Y_OFFSET};
            blackRectangleForFillingEnemyHP.setSize(healthBarOffset);
        }
        else {
            SetZeroSize(blackRectangleForFillingEnemyHP);
        }
    }
    else if (name == "strongEnemy") {
        if ((Health > 0) && (Health <= enemiesHandler.hardEnemy.health)) {
            healthBarOffset = {
                    (BAR_WIDTH * (enemiesHandler.hardEnemy.health - Health) / enemiesHandler.hardEnemy.health),
                    Y_OFFSET};
            blackRectangleForFillingEnemyHP.setSize(healthBarOffset);
        }
        else {
            SetZeroSize(blackRectangleForFillingEnemyHP);
        }
    }
}

void Bar::UpdateProtagonist(size_t Health, size_t Shield) {
    if ((Health > 0) && (Health <= playerProperties.HEALTH)) {
        healthBarOffset = {(BAR_WIDTH * (playerProperties.HEALTH - Health) / playerProperties.HEALTH), Y_OFFSET};
        blackRectangleForFillingPlayerHP.setSize(healthBarOffset);
    }
    else {
        SetZeroSize(blackRectangleForFillingPlayerHP);
    }
    if ((Shield > 0) && (Shield <= playerProperties.shield)) {
        shieldBarOffset = {(BAR_WIDTH * (playerProperties.shield - Shield) / playerProperties.shield), Y_OFFSET};
        blackRectangleForFillingPlayerShield.setSize(shieldBarOffset);
    }
    else {
        SetZeroSize(blackRectangleForFillingPlayerShield);
    }
}

void Bar::Draw(sf::RenderWindow &window) {
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    playerBarHealth.setPosition((center.x - size.x / 2), center.y - size.y / 2 + 15);
    playerBarShield.setPosition((center.x - size.x / 2), center.y - size.y / 2 + 45);
    blackRectangleForFillingPlayerHP.setPosition((center.x - size.x / 2) + 200, center.y - size.y / 2 + 30);
    blackRectangleForFillingPlayerShield.setPosition((center.x - size.x / 2) + 200, center.y - size.y / 2 + 60);
    blackRectangleForFillingEnemyHP.setPosition((center.x + 100), (center.y + size.y / 2.2f) + 15);
    enemyBar.setPosition((center.x - 100), (center.y + size.y / 2.2f));

    window.draw(playerBarHealth);
    window.draw(playerBarShield);
    window.draw(enemyBar);
    window.draw(blackRectangleForFillingEnemyHP);
    window.draw(blackRectangleForFillingPlayerHP);
    window.draw(blackRectangleForFillingPlayerShield);
}
