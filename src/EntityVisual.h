#pragma once
#include <SFML/Graphics.hpp>
#include "resource.h"

struct EntityVisual {
public:
    EasyEnemy easyEnemy;
    PlayerProperties playerProperties;
    Vector2f position;
    Vector2i size;
    Texture texture;
    Sprite sprite;

    EntityVisual(Image &image, Vector2f Position, Vector2i Size);

    FloatRect getRect();

};