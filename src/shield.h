#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Shield {
public:
    Texture texture1;
    Sprite shield;
    Shield();
    void Draw(RenderWindow & window, Vector2f position);
};