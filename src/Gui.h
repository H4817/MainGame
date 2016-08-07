#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Gui {
public:
    Gui();

    void UpdateEnemy(size_t Health, const string &name);

    void UpdateProtagonist(size_t Health, size_t Shield);

    void Draw(sf::RenderWindow &window, size_t weaponNumber, size_t amountOfMissiles, size_t amountOfEnemies);

private:

    void SetZeroSize(sf::RectangleShape &rectangleShape);

    void SetSpritesPosition(sf::RenderWindow &window);

    PlayerProperties playerProperties;
    EnemiesHandler enemiesHandler;

    sf::Font font;
    sf::Text missilesAmount;
    sf::Text levelStatus;

    sf::RectangleShape blackRectangleForFillingEnemyHP;
    sf::RectangleShape blackRectangleForFillingPlayerHP;
    sf::RectangleShape blackRectangleForFillingPlayerShield;
    const size_t BAR_WIDTH = 191;
    const size_t Y_OFFSET = 10;
    sf::Image entitiesBar;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture entitiesTexture;
    sf::Sprite playerBarHealth;
    sf::Sprite playerBarShield;
    sf::Sprite enemyBar;
    sf::Sprite weaponIcon;
    sf::Vector2f healthBarOffset;
    sf::Vector2f shieldBarOffset;
};

