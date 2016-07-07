#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bar {
public:
    Bar();

    void UpdateEnemy(size_t Health);

    void UpdateProtagonist(size_t Health, size_t Shield);

    void Draw(sf::RenderWindow &window);

private:

    PlayerProperties playerProperties;
    EnemiesHandler enemiesHandler;

    sf::RectangleShape enemyBarBlack;
    sf::RectangleShape playerBarBlackHP;
    sf::RectangleShape playerBarBlackShield;

    sf::Image entitiesBar;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture entitiesTexture;
    sf::Sprite playerBarHealth;
    sf::Sprite playerBarShield;
    sf::Sprite enemyBar;
    sf::Vector2f healthBarOffset;
    sf::Vector2f shieldBarOffset;
};

