#include "Application.h"


void getPlayerCoordinateForView(Vector2f position) {
    Vector2f centerPosition = {position.x, position.y};
    if (position.x < MAP_WIDTH.x) centerPosition.x = MAP_WIDTH.x;
    if (position.x > MAP_WIDTH.y) centerPosition.x = MAP_WIDTH.y;
    if (position.y < MAP_HEIGHT.x) centerPosition.y = MAP_HEIGHT.x;
    if (position.y > MAP_HEIGHT.y) centerPosition.y = MAP_HEIGHT.y;
    view.setCenter(centerPosition.x, centerPosition.y);
}

float RunTimer(Application &application) {
    float time_ms = application.clock.getElapsedTime().asMicroseconds();
    application.clock.restart();
    time_ms /= 1000;
    return time_ms;
}

void ProcessEvents(RenderWindow &window, Player &protagonist, Application &application) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed || event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::F) {
                application.playerShieldIsActive = !application.playerShieldIsActive;
            }

            else if (event.key.code == sf::Keyboard::Q) {
                if (protagonist.GetCurrentWeapon() == 0)
                    protagonist.SetCurrentWeapon(1);
                else
                    protagonist.SetCurrentWeapon(0);
            }

            else if (event.key.code == sf::Keyboard::R && protagonist.GetShield() > 0) {

                if (protagonist.GetCurrentWeapon() == 0) {
                    application.entities.push_back(
                            new Bullet(application.imageAssets.bulletImage, application.objects, protagonist.position,
                                       application.playerProperties.playerBullet.SIZE, application.playerPosition,
                                       "Bullet"));
                    protagonist.SetShield(protagonist.GetShield() - 2);
                    application.gui.UpdateProtagonist(static_cast<size_t >(protagonist.health),
                                                      static_cast<size_t >(protagonist.GetShield()));
                }

                else if (protagonist.GetAmountOfMissile() > 0) {
                    application.entities.push_back(new Rocket(application.imageAssets.rocketImage, application.objects,
                                                              protagonist.position,
                                                              application.playerProperties.simpleRocket.SIZE,
                                                              application.playerPosition, "Rocket"));
                    protagonist.SetAmountOfMissile(protagonist.GetAmountOfMissile() - 1);
                }

            }

        }
    }
}

void GetMousePosition(RenderWindow &window, Vector2f &playerPosition) {
    Vector2i pixelPos = Mouse::getPosition(window);
    playerPosition = window.mapPixelToCoords(pixelPos);
}

void InitializeImages(Application &application) {
    application.lvl.LoadFromFile("Assets/map1.tmx");
    application.imageAssets.bulletImage.loadFromFile("IMG/PlasmaBullet.png");
    application.imageAssets.rocketImage.loadFromFile("IMG/rocket1.png");
    application.imageAssets.smartRocketImage.loadFromFile("IMG/SmartRocket.png");
    application.imageAssets.enemyBulletImage.loadFromFile("IMG/RedPlasmaBullet.png");
    application.imageAssets.heroImage.loadFromFile("IMG/888.png");
    application.imageAssets.easyEnemyImage.loadFromFile("IMG/EasyEnemyYellowThrust1.png");
    application.imageAssets.mediumEnemyImage.loadFromFile("IMG/MediumEnemyWithGreenThrust.png");
    application.imageAssets.strongEnemyImage.loadFromFile("IMG/StrongEnemyWithGreenThrust.png");
    application.imageAssets.asteroid.loadFromFile("IMG/Asteroids/strip_rock_type_D.png");
}

Object InitializePlayer(Application &application) {
    Object player = application.lvl.GetObject("player");
    return player;
}

bool IsNotAliveEntity(Entity *entity) {
    return !entity->alive;
}

bool IsAggro(const Vector2f &protagonistPosition, const Vector2f &enemyPosition, const size_t &distance) {
    return ((abs(protagonistPosition.x - enemyPosition.x)) < distance &&
            (abs(protagonistPosition.y - enemyPosition.y)) < distance);
}

void AppendEnemiesBullets(Application &application, Entity *it, Player &protagonist, float &localTime) {
    if ((it->name == "easyEnemy") &&
        IsAggro(protagonist.position, it->position, application.enemiesHandler.easyEnemy.AGGRO_DISTANCE) &&
        localTime >= 35000 && localTime <= 50000) {
        application.entities.push_back(
                new Bullet(application.imageAssets.enemyBulletImage, application.objects, it->position,
                           application.enemiesHandler.easyEnemy.easyEnemyBullet.SIZE,
                           protagonist.position, "EnemyBullet"));
        localTime += 15000;
    }

    else if ((it->name == "mediumEnemy") &&
             IsAggro(protagonist.position, it->position, application.enemiesHandler.mediumEnemy.AGGRO_DISTANCE) &&
             localTime >= 70000 && localTime <= 86000) {
        application.entities.push_back(
                new Rocket(application.imageAssets.rocketImage, application.objects,
                           it->position, application.enemiesHandler.mediumEnemy.simpleRocket.SIZE,
                           protagonist.position, "EnemyRocket"));
        localTime += 16000;
    }

    else if ((it->name == "strongEnemy") &&
             IsAggro(protagonist.position, it->position, application.enemiesHandler.hardEnemy.AGGRO_DISTANCE)) {

        if (localTime >= 50000 && localTime <= 70000) {
            application.entities.push_back(
                    new Bullet(application.imageAssets.enemyBulletImage, application.objects,
                               it->position, application.enemiesHandler.easyEnemy.easyEnemyBullet.SIZE,
                               protagonist.position, "EnemyBullet"));
            localTime += 20000;
        }

        if (localTime >= 86000 && localTime <= 100000) {
            application.entities.push_back(
                    new SmartRocket(application.imageAssets.smartRocketImage, application.objects,
                                    it->position, application.enemiesHandler.hardEnemy.smartRocket.SIZE,
                                    protagonist.position, "EnemySmartRocket"));
            localTime += 14000;
        }

    }

    if (localTime > 100000) {
        localTime = 0.f;
    }

}

void ProcessEntities(float &time_ms, Application &application, Player &protagonist) {
    auto new_end = std::remove_if(application.entities.begin(), application.entities.end(), IsNotAliveEntity);
    application.entities.erase(new_end, application.entities.end());
    static float localTime = 0.f;
    for (auto it : application.entities) {
        localTime += time_ms;
        AppendEnemiesBullets(application, it, protagonist, localTime);
        it->Update(time_ms, application.objects);
    }
}

bool IsShieldActive(const Application &application, const Player &protagonist) {
    return application.playerShieldIsActive && protagonist.GetShield() > 0;
}

bool IsBullet(const string &name) {
    return (name == "Bullet" || name == "Rocket" || name == "EnemyBullet" || name == "EnemyRocket" ||
            name == "EnemySmartRocket");
}

bool IsEnemy(const string &name) {
    return (name == "easyEnemy" || name == "mediumEnemy" || name == "strongEnemy");
}

void ProcessDamage(Player &protagonist, Application &application) {
    for (auto it : application.entities) {
        for (auto at : application.entities) {
            if (it->RetRect().intersects(at->RetRect())) {

                if (IsEnemy(it->name)) {

                    if (at->name == "Bullet") {
                        it->health -= application.playerProperties.playerBullet.DAMAGE;
                        at->alive = false;
                        application.gui.UpdateEnemy(static_cast<size_t >(it->health), it->name);
                    }

                    else if (at->name == "Rocket") {
                        it->health -= application.playerProperties.simpleRocket.DAMAGE;
                        at->name = "explosion";
                        application.gui.UpdateEnemy(static_cast<size_t >(it->health), it->name);
                    }

                }

                else if (at->name == "Asteroid") {
                    if (it->name != "Asteroid") {
                        if (IsBullet(it->name)) {
                            it->alive = false;
                        }
                        else {
                            it->health -= 100;
                        }
                        if (it->name != "HealthReward" && it->name != "ShieldReward")
                            at->name = "explosion";
                    }
                }

            }

        }
        if (it->RetRect().intersects(protagonist.RetRect())) {
            if (it->name == "EnemyBullet") {
                if (IsShieldActive(application, protagonist)) {
                    protagonist.SetShield(
                            protagonist.GetShield() -
                            static_cast<int>(application.enemiesHandler.easyEnemy.easyEnemyBullet.DAMAGE / 2));
                }
                else {
                    protagonist.health -= application.enemiesHandler.easyEnemy.easyEnemyBullet.DAMAGE;
                }
                it->alive = false;
            }
            else if (it->name == "EnemyRocket" || it->name == "EnemySmartRocket") {
                if (IsShieldActive(application, protagonist)) {
                    protagonist.SetShield(
                            protagonist.GetShield() -
                            static_cast<int>(application.enemiesHandler.mediumEnemy.simpleRocket.DAMAGE / 2));
                }
                else {
                    protagonist.health -= application.enemiesHandler.mediumEnemy.simpleRocket.DAMAGE;
                }
                it->name = "explosion";
            }
            else if (IsEnemy(it->name)) {
                it->boost.x = 0;
                it->boost.y = 0;
                it->health -= (application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                               abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                if (protagonist.GetShield() > 0 && application.playerShieldIsActive) {
                    protagonist.SetShield(protagonist.GetShield() -
                                          static_cast<int>((application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                                            abs(static_cast<long>(it->velocity.x + it->velocity.y) /
                                                                2))));
                }
                else {
                    protagonist.health -= (application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                           abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                }
                application.gui.UpdateEnemy(static_cast<size_t>(it->health), it->name);
            }
            else if (it->name == "ShieldReward") {
                protagonist.SetShield(protagonist.GetShield() + 30);
                it->alive = false;
            }
            else if (it->name == "HealthReward") {
                protagonist.health += 30;
                it->alive = false;
            }
            application.gui.UpdateProtagonist(static_cast<size_t>(protagonist.health),
                                              static_cast<size_t>(protagonist.GetShield()));
        }
    }
}

void AppendEnemies(Application &application) {

    for (int i = 0; i < application.enemiesContainer.easyOpponent.size(); i++) {
        application.entities.push_back(
                new CEasyEnemy(application.imageAssets.easyEnemyImage, application.objects,
                               {application.enemiesContainer.easyOpponent[i].rect.left,
                                application.enemiesContainer.easyOpponent[i].rect.top},
                               application.enemiesHandler.easyEnemy.SIZE, application.playerPosition,
                               "easyEnemy"));
        ++application.amountOfEnemies;
    }

    for (int i = 0; i < application.enemiesContainer.mediumOpponent.size(); i++) {
        application.entities.push_back(
                new CMediumEnemy(application.imageAssets.mediumEnemyImage, application.objects,
                                 {application.enemiesContainer.mediumOpponent[i].rect.left,
                                  application.enemiesContainer.mediumOpponent[i].rect.top},
                                 application.enemiesHandler.mediumEnemy.SIZE, application.playerPosition,
                                 "mediumEnemy"));
        ++application.amountOfEnemies;
    }

    for (int i = 0; i < application.enemiesContainer.strongOpponent.size(); i++) {
        application.entities.push_back(
                new CStrongEnemy(application.imageAssets.strongEnemyImage, application.objects,
                                 {application.enemiesContainer.strongOpponent[i].rect.left,
                                  application.enemiesContainer.strongOpponent[i].rect.top},
                                 application.enemiesHandler.hardEnemy.SIZE, application.playerPosition,
                                 "strongEnemy"));
        ++application.amountOfEnemies;
    }

}

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window) {
    if (!protagonist.alive) {
        window.close();
        cout << "game over\n";
    }

}

void AppendAsteroids(size_t amount, Application &application) {
    for (size_t i = 0; i < amount; ++i) {
        application.entities.push_back(
                new Asteroid(application.imageAssets.asteroid,
                             {static_cast<float>(rand() % (application.parameters.MAP_SIZE.x - 20 + 1) + 20),
                              static_cast<float>(rand() % (application.parameters.MAP_SIZE.y - 10 + 1) + 10)},
                             {65, 64},
                             "Asteroid"));
    }
}

void Draw(RenderWindow &window, Player &protagonist, Application &application) {
    window.clear();
    application.lvl.Draw(window);
    for (auto it : application.entities) {
        window.draw((it)->sprite);
    }
    window.draw(protagonist.sprite);
    if (application.playerShieldIsActive && protagonist.GetShield() > 0) {
        application.shield.Draw(window, protagonist.position);
    }
    application.gui.Draw(window, protagonist.GetCurrentWeapon(), protagonist.GetAmountOfMissile());
    application.aim.Draw(window);
    if (protagonist.GetState() == 0) {
        application.thrust.Draw(window, protagonist.position, application.objects.playerRotation);
    }
    window.display();
}

bool AllEnemiesDead(const Application &application) {
    return application.amountOfEnemies == 0;
}

void MainLoop(RenderWindow &window, Application &application, Player &protagonist) {

    while (window.isOpen()) {
        GetMousePosition(window, application.playerPosition);
        float time_ms = RunTimer(application);
        ProcessEvents(window, protagonist, application);
        protagonist.rotation_GG(application.playerPosition);
        protagonist.Update(time_ms, application.objects);
        ProcessEntities(time_ms, application, protagonist);
        ProcessDamage(protagonist, application);
        CheckExistenceProtagonist(protagonist, window);
        window.setView(view);
        Draw(window, protagonist, application);
        if (AllEnemiesDead(application))
            break;
    }

}

void GetMapObjects(Application &application) {
    application.enemiesContainer.easyOpponent = application.lvl.GetObjects("easyEnemy");
    application.enemiesContainer.mediumOpponent = application.lvl.GetObjects("mediumEnemy");
    application.enemiesContainer.strongOpponent = application.lvl.GetObjects("hardEnemy");
}

Player CreatePlayer(Application &application) {
    Object player = InitializePlayer(application);
    Player protagonist(application.imageAssets.heroImage, {player.rect.left, player.rect.top},
                       application.playerProperties.SIZE, "player");
    application.entities.push_back(&protagonist);
    return protagonist;
}

void InitializeWindow(Application &application) {
    application.window.create(
            sf::VideoMode(application.parameters.WINDOW_SIZE.first, application.parameters.WINDOW_SIZE.second), "Game");
    application.window.setMouseCursorVisible(false);
    application.window.setFramerateLimit(60);
    application.window.setVerticalSyncEnabled(true);
    view.reset(
            sf::FloatRect(0, 0, application.parameters.WINDOW_SIZE.first, application.parameters.WINDOW_SIZE.second));
}


void Initialize(Application &application) {
    InitializeWindow(application);
    InitializeImages(application);
    AppendAsteroids(10, application);
    GetMapObjects(application);
    AppendEnemies(application);
}

void SetLevel(Application &application) {

}

void Run(RenderWindow &window, Application &application, Player &protagonist) {
    MainLoop(window, application, protagonist);
}

void StartGame() {
    Application application;
    Initialize(application);
    SetLevel(application);
    auto protagonist = CreatePlayer(application);
    Run(application.window, application, protagonist);
}
