#pragma once
#include <SFML/Graphics.hpp>
#include "level.h"
#include <list>
#include "resource.h"


using namespace sf;
using namespace std;

struct Entity {
public:
    EasyEnemy easyEnemy;
    Parameters parameters;
    PlayerProperties playerProperties;
    int healthEasyEnemy = 200;
    float speed;
    float moveTimer;
    Vector2f boost;
    Vector2f position;
    Vector2f temp;
    Vector2f temp1;
    Vector2i size;
    bool alive;
    bool isMove;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image &image, Vector2f Position, Vector2i Size, String Name);
    FloatRect getRect();
    virtual void update(float time, MapObjects & objects) = 0;
};