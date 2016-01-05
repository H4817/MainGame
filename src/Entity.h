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
    MapObjects objects;
    Parameters parameters;
    PlayerProperties playerProperties;
    float speed;
    float moveTimer;
    Vector2f boost;
    Vector2f position;
    Vector2f temp;
    Vector2i size;
    int health;
    bool alive;
    bool isMove;
    Texture texture;
    Sprite sprite;
    String name;
    Entity(Image &image, Vector2f Position, Vector2i Size, String Name);
    FloatRect getRect();
    virtual void update(float time) = 0;
};