#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Shield {
public:
    Texture texture1;
    Image shieldImage;
    Sprite shield;
    Shield();
    void draw(RenderWindow & window, Vector2f position);
};