#pragma once
#include <SFML/Graphics.hpp>
#include "level.h"
#include "resource.h"
#include <list>


using namespace sf;
using namespace std;

struct Entity {
public:
    float speed;
    float moveTimer;
    Vector2f boost;
    Vector2f position;
    int health;
    Vector2i size;
    bool alive;
    bool isMove;
    bool isSelect;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image &image, Vector2f Position, Vector2i Size, String Name);
    FloatRect getRect();
    virtual void update(float time) = 0;
};