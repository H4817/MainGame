#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


struct EntityVisual {
public:
    Vector2f position;
    Vector2i size;
    Texture texture;
    Sprite sprite;

    EntityVisual(Image &image, Vector2f Position, Vector2i Size);

    FloatRect getRect();

};