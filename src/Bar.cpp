#include "Bar.h"

Bar::Bar() {
    texture1.loadFromFile("IMG/EnemyBar.png");
    playerBarHealth.setTexture(texture1);

    texture2.loadFromFile("IMG/BlueBar.png");
    playerBarShield.setTexture(texture2);

    texture3.loadFromFile("IMG/plasma_icon.png");
    plasmaIcon.setTexture(texture3);

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
    rectangleShape.setSize({static_cast<float>(BAR_WIDTH), static_cast<float>(Y_OFFSET)});
}

void Bar::UpdateEnemy(size_t Health, const string &name) {
    if (name == "easyEnemy") {
        if ((Health > 0) && (Health <= enemiesHandler.easyEnemy.health)) {
            healthBarOffset = {
                    (static_cast<float>(BAR_WIDTH * (enemiesHandler.easyEnemy.health - Health) /
                                        enemiesHandler.easyEnemy.health)),
                    static_cast<float>(Y_OFFSET)};
            blackRectangleForFillingEnemyHP.setSize(healthBarOffset);
        }
        else {
            SetZeroSize(blackRectangleForFillingEnemyHP);
        }
    }
    else if (name == "mediumEnemy") {
        if ((Health > 0) && (Health <= enemiesHandler.mediumEnemy.health)) {
            healthBarOffset = {static_cast<float>(
                                       (BAR_WIDTH * (enemiesHandler.mediumEnemy.health - Health) /
                                        enemiesHandler.mediumEnemy.health)),
                               static_cast<float> (Y_OFFSET)};
            blackRectangleForFillingEnemyHP.setSize(healthBarOffset);
        }
        else {
            SetZeroSize(blackRectangleForFillingEnemyHP);
        }
    }
    else if (name == "strongEnemy") {
        if ((Health > 0) && (Health <= enemiesHandler.hardEnemy.health)) {
            healthBarOffset = {static_cast<float> (
                                       (BAR_WIDTH * (enemiesHandler.hardEnemy.health - Health) /
                                        enemiesHandler.hardEnemy.health)),
                               static_cast<float>(Y_OFFSET)};
            blackRectangleForFillingEnemyHP.setSize(healthBarOffset);
        }
        else {
            SetZeroSize(blackRectangleForFillingEnemyHP);
        }
    }
}

void Bar::UpdateProtagonist(size_t Health, size_t Shield) {
    if ((Health > 0) && (Health <= playerProperties.HEALTH)) {
        healthBarOffset = {
                static_cast<float>((BAR_WIDTH * (playerProperties.HEALTH - Health) / playerProperties.HEALTH)),
                static_cast<float >(Y_OFFSET)};
        blackRectangleForFillingPlayerHP.setSize(healthBarOffset);
    }
    else {
        SetZeroSize(blackRectangleForFillingPlayerHP);
    }
    if ((Shield > 0) && (Shield <= playerProperties.shield)) {
        shieldBarOffset = {static_cast<float>((BAR_WIDTH * (playerProperties.shield - Shield) / playerProperties.shield)),
                           static_cast<float>(Y_OFFSET)};
        blackRectangleForFillingPlayerShield.setSize(shieldBarOffset);
    }
    else {
        SetZeroSize(blackRectangleForFillingPlayerShield);
    }
}

void Bar::SetSpritesPosition(sf::RenderWindow &window) {
    sf::Vector2f center = window.getView().getCenter();
    sf::Vector2f size = window.getView().getSize();

    playerBarHealth.setPosition((center.x - size.x / 2), center.y - size.y / 2 + 15);
    playerBarShield.setPosition((center.x - size.x / 2), center.y - size.y / 2 + 45);
    blackRectangleForFillingPlayerHP.setPosition((center.x - size.x / 2) + 200, center.y - size.y / 2 + 30);
    blackRectangleForFillingPlayerShield.setPosition((center.x - size.x / 2) + 200, center.y - size.y / 2 + 60);
    blackRectangleForFillingEnemyHP.setPosition((center.x + 100), (center.y + size.y / 2.2f) + 15);
    enemyBar.setPosition((center.x - 100), (center.y + size.y / 2.2f));
    plasmaIcon.setPosition((center.x - size.x / 2), (center.y + size.y / 2.4f));
}

void Bar::Draw(sf::RenderWindow &window) {
    SetSpritesPosition(window);
    window.draw(playerBarHealth);
    window.draw(playerBarShield);
    window.draw(enemyBar);
    window.draw(blackRectangleForFillingEnemyHP);
    window.draw(blackRectangleForFillingPlayerHP);
    window.draw(blackRectangleForFillingPlayerShield);
    window.draw(plasmaIcon);
}
