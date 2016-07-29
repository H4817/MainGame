#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bar {
public:
    Bar();

    void UpdateEnemy(size_t Health, const string & name);

    void UpdateProtagonist(size_t Health, size_t Shield);

    void Draw(sf::RenderWindow &window);

private:

    void SetZeroSize(sf::RectangleShape & rectangleShape);

    void SetSpritesPosition(sf::RenderWindow &window);

    PlayerProperties playerProperties;
    EnemiesHandler enemiesHandler;

    sf::RectangleShape blackRectangleForFillingEnemyHP;
    sf::RectangleShape blackRectangleForFillingPlayerHP;
    sf::RectangleShape blackRectangleForFillingPlayerShield;
    const size_t BAR_WIDTH = 191;
    const size_t Y_OFFSET = 10;
    sf::Image entitiesBar;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture entitiesTexture;
    sf::Sprite playerBarHealth;
    sf::Sprite playerBarShield;
    sf::Sprite enemyBar;
    sf::Sprite plasmaIcon;
    sf::Vector2f healthBarOffset;
    sf::Vector2f shieldBarOffset;
};

