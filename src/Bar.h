#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar {
public:
    Image image;
    Image entitiesBar;
    Texture t;
    Texture entitiesTexture;
    Sprite s;
    Sprite bar2;
    Vector2f barOffset;
    const int maxHealth = 200;
    const int halfScreen = 2;
    RectangleShape bar;

    LifeBar();

    void updateEnemy(int Shields, int Health);

    void draw(RenderWindow &window);
};

