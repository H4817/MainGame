#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Bar.h"
#include "Asteroid.h"
#include "Thrust.h"
#include "shield.h"
#include "aim.h"
#include <memory>


namespace {
    const Vector2f MAP_WIDTH = {960, 2270};
    const Vector2f MAP_HEIGHT = {530, 2600};
    sf::View view;
}

struct EnemiesContainer {
    std::vector<Object> easyOpponent;
    std::vector<Object> mediumOpponent;
    std::vector<Object> strongOpponent;
};
struct ImageAssets {
    Image heroImage;
    Image easyEnemyImage;
    Image mediumEnemyImage;
    Image strongEnemyImage;
    Image bulletImage;
    Image rocketImage;
    Image smartRocketImage;
    Image enemyBulletImage;
    Image asteroid;
};

struct Application {
    bool playerShieldIsActive = false;
    Clock clock;
    Level lvl;
    std::list<Entity *> entities;
    Bar bar;
    Shield shield;
    Aim aim;
    EnemiesHandler enemiesHandler;
    EnemiesContainer enemiesContainer;
    PlayerProperties playerProperties;
    ImageAssets imageAssets;
    MapObjects objects;
    Parameters parameters;
    Thrust thrust;
    Vector2f playerPosition;
};

void StartGame();

void MainLoop(RenderWindow &window, Application &application, Player &protagonist);

void GetMapObjects(Application &application);

Player CreatePlayer(Application &application);