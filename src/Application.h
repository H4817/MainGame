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
#include "Menu.h"
#include "GameState.h"
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
    Vector2f playerPosition;
    size_t amountOfEnemies = 0;
    RenderWindow window;
};

void StartGame(size_t level);

bool IsEnemy(const string &name);

bool IsReward(const string &name);

void MainLoop(Application &application, Player &protagonist);

Player CreatePlayer(Application &application);

void Initialize(Application &application);

void SetLevel(Application &application, size_t level);

void Run(Application &application, size_t level);

void InitializeWindow(Application &application);

void CloseWindowWhenItWasInterrupted(Application &application, const Event &event);

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window);

void DrawMenu(Application &application);

void ProcessMeleeDamage(Entity *entity, Application &application, Player &protagonist);

void ProcessAsteroidDamage(Entity *entity1, Entity *entity2, Application &application, Player &protagonist);

void ProcessDistanceDamage(Entity *entity, Application &application, Player &protagonist);

void SetPlayerShield(Player &protagonist, int shield);

void SetPlayerHealth(Player &protagonist, int health);
