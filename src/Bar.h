#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar {
public:
    LifeBar();

    const int maxHealthEnemy = 200;
    const int maxHealthPlayer = 200;
    const int maxShieldPlayer = 200;
    const int halfScreen = 2;

    void updateEnemy(int & Health);

    void updateSelf(int & Health, int & Shield);

    void draw(RenderWindow &window);

private:

    RectangleShape enemyBarBlack;
    RectangleShape playerBarBlackHP;
    RectangleShape playerBarBlackShield;


    Image entitiesBar;
    Texture texture1;
    Texture texture2;
    Texture entitiesTexture;
    Sprite playerBarHealth;
    Sprite playerBarShield;
    Sprite enemyBar;
    Vector2f healthBarOffset;
    Vector2f shieldBarOffset;
};

