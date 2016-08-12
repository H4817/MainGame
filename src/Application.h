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

    Application() : gameState(MENU) {
        mapInfo = {{"Assets/Level_1.tmx", 0},
                   {"Assets/map1.tmx",    10}};
        mapSize = {{980, 650}, {2270, 2600}};

    };

    Menu menu;
    GameState gameState;
    Level map;
    vector<pair<string, size_t>> mapInfo;
    vector<pair<size_t, size_t >> mapSize;
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
    //Thrust thrust;
    Vector2f playerPosition;
    size_t level = 0;
    size_t amountOfEnemies = 0;
    RenderWindow window;
};

void StartGame();

bool IsEnemy(const string &name);

bool IsReward(const string &name);

void MainLoop(Application &application, Player &protagonist);

Player CreatePlayer(Application &application);

void Initialize(Application &application);

void SetLevel(Application &application);

void Run(Application &application);

void InitializeWindow(Application &application);

void CloseWindowWhenItWasInterrupted(Application &application, const Event &event);

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window);

void DrawMenu(Application &application);

void ProcessMeleeDamage(Entity *entity, Application &application, Player &protagonist);

void ProcessAsteroidDamage(Entity *entity1, Entity *entity2, Application &application, Player &protagonist);

void ProcessDistanceDamage(Entity *entity, Application &application, Player &protagonist);

void SetPlayerShield(Player & protagonist, int shield);

void SetPlayerHealth(Player & protagonist, int health);
