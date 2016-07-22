#pragma once
#include <SFML/Graphics.hpp>
#include "level.h"
#include <list>
#include "resource.h"
#include <math.h>
#include <memory>

using namespace sf;
using namespace std;

struct Entity {
public:
    Entity(Image &image, Vector2f Position, Vector2i Size, String Name);
    Vector2f velocity;
    Parameters parameters;
    int enemyHealth = 200;
    float speed;
    const float DEG_TO_RAD = 0.017453f;
    Vector2f boost;
    Vector2f position;
    Vector2f temp;
    Vector2i size;
    bool alive;
    bool isMove;
    Texture texture;
    Sprite sprite;
    String name;
    FloatRect RetRect();
    void SetRightPosition(Vector2f & position);
    bool IsCharacter();
    virtual void Update(float time, MapObjects &objects) = 0;
};

