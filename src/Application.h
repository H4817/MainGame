#pragma once

#include "LevelInfo.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Gui.h"
#include "Asteroid.h"
#include "Thrust.h"
#include "shield.h"
#include "aim.h"
#include "GameState.h"
#include "Menu/Menu.h"
#include <memory>

namespace {
    Vector2f MAP_SIZE;
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

    Application() {
        gameState = GAME;
        mapInfo = {{"Assets/Level_1.tmx", 0},
                   {"Assets/Level_2.tmx", 0},
                   {"Assets/Level_3.tmx", 5},
                   {"Assets/map1.tmx",    15}

        };
    };

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
    Vector2f playerPosition;
    size_t amountOfEnemies = 0;
};

void StartGame(size_t level, RenderWindow &window, Menu & menu);

bool IsEnemy(const string &name);

bool IsReward(const string &name);

void MainLoop(Application &application, Player &protagonist, RenderWindow &window, Menu & menu);

Player CreatePlayer(Application &application);

void Initialize(Application &application, RenderWindow &window);

void SetLevel(Application &application, size_t level);

void Run(Application &application, size_t level, RenderWindow &window, Menu & menu);

void InitializeWindow(Application &application, RenderWindow &window);

void CloseWindowWhenItWasInterrupted(const Event &event, RenderWindow &window);

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window);

void DrawMenu(RenderWindow &window, Menu & menu, GameState & gameState);

void ProcessMeleeDamage(Entity *entity, Application &application, Player &protagonist);

void ProcessAsteroidDamage(Entity *entity1, Entity *entity2, Application &application, Player &protagonist);

void ProcessDistanceDamage(Entity *entity, Application &application, Player &protagonist);

void SetPlayerShield(Player &protagonist, int shield);

void SetPlayerHealth(Player &protagonist, int health);
