#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar {
public:
    Image entitiesBar;
    Texture texture1;
    Texture texture2;
    Texture entitiesTexture;
    Sprite playerBarHealth;
    Sprite playerBarShield;
    Sprite enemyBar;
    Vector2f healthBarOffset;
    Vector2f shieldBarOffset;
    const int maxHealthEnemy = 200;
    const int maxHealthPlayer = 200;
    const int maxShieldPlayer = 200;
    const int halfScreen = 2;
    RectangleShape enemyBarBlack;
    RectangleShape playerBarBlackHP;
    RectangleShape playerBarBlackShield;

    LifeBar();

    void updateEnemy(int & Health);

    void updateSelf(int & Health, int & Shield);

    void draw(RenderWindow &window);
};

