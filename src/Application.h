#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Gui.h"
#include "Asteroid.h"
#include "Thrust.h"
#include "shield.h"
#include "aim.h"
#include "Menu.h"
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

enum GameState {
    MENU,
    PAUSE,
    GAME
};

struct Application {

    Application() : gameState(MENU) {
        mapInfo = {{"Assets/map1.tmx",    0},
                   {"Assets/Level_1.tmx", 10}};
    };

//    Menu menu;
    GameState gameState;
    Level map;
    vector<pair<string, size_t>> mapInfo;
    bool playerShieldIsActive = false;
    Clock clock;
    std::list<Entity *> entities;
    Gui gui;
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
    size_t level = 0;
    size_t amountOfEnemies = 0;
    RenderWindow window;
};

void StartGame();

bool IsEnemy(const string &name);

void MainLoop(Application &application, Player &protagonist);

Player CreatePlayer(Application &application);

void Initialize(Application &application);

void SetLevel(Application &application);

void Run(Application &application, Player &protagonist);

void InitializeWindow(Application &application);
