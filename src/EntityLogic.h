#pragma once

#include <SFML/Graphics.hpp>
#include "level.h"
#include <list>
#include "resource.h"
#include "EntityVisual.h"


using namespace sf;
using namespace std;

struct EntityLogic {
public:
    EasyEnemy easyEnemy;
    Parameters parameters;
    PlayerProperties playerProperties;
    EntityVisual * Visual;
    float speed;
    float moveTimer;
    Vector2f boost;
    Vector2f temp;
    int health;
    bool alive;
    bool isMove;
    String name;

    EntityLogic(String Name, EntityVisual * visual);

    FloatRect getRect(EntityVisual & visual);

    virtual void update(float time, MapObjects & objects, std::list<EntityVisual*> & visual) = 0;
};