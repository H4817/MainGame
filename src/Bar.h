#pragma once
#include <SFML/Graphics.hpp>

class Bar {
public:
    Bar();

    void UpdateEnemy(int &Health);

    void UpdateProtagonist(int &Health, int &Shield);

    void draw(sf::RenderWindow &window);

private:
    const size_t ENEMY_MAX_HEALTH = 200;
    const size_t PLAYER_MAX_HEALTH = 200;
    const size_t SHIELD_CAPACITY = 200;

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

