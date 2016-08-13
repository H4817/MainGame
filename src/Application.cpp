#include "Application.h"
#include "MapSize.h"

void SetMapSize(Application &application) {
    MAP_SIZE = {mapSize[currentLevel].first, mapSize[currentLevel].second};
}

void getPlayerCoordinateForView(Vector2f position) {
    Vector2f centerPosition = {position.x, position.y};
    if (position.x < 960) centerPosition.x = 960;
    if (position.x > MAP_SIZE.x) centerPosition.x = MAP_SIZE.x;
    if (position.y < 530) centerPosition.y = 530;
    if (position.y > MAP_SIZE.y) centerPosition.y = MAP_SIZE.y;
    view.setCenter(centerPosition.x, centerPosition.y);
}

float RunTimer(Application &application) {
    float time_ms = application.clock.getElapsedTime().asMicroseconds();
    application.clock.restart();
    time_ms /= 1000;
    return time_ms;
}

void ProcessEvents(Player &protagonist, Application &application) {
    sf::Event event;
    while (application.window.pollEvent(event)) {
        CloseWindowWhenItWasInterrupted(application, event);
        if (event.type == Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::F) {
                application.playerShieldIsActive = !application.playerShieldIsActive;
            }
            else if (event.key.code == sf::Keyboard::D) {
                application.gameState = PAUSE;
            }

            else if (event.key.code == sf::Keyboard::Q) {
                if (protagonist.GetCurrentWeapon() == 0)
                    protagonist.SetCurrentWeapon(1);
                else
                    protagonist.SetCurrentWeapon(0);
            }

            else if (event.key.code == sf::Keyboard::R) {

                if (protagonist.GetCurrentWeapon() == 0 && protagonist.GetShield() > 0) {
                    application.entities.push_back(
                            new Bullet(application.imageAssets.bulletImage, application.objects, protagonist.position,
                                       application.playerProperties.playerBullet.SIZE, application.playerPosition,
                                       "Bullet"));
                    protagonist.SetShield(protagonist.GetShield() - 2);
                    application.gui.UpdateProtagonist(static_cast<size_t >(protagonist.GetHealth()),
                                                      static_cast<size_t >(protagonist.GetShield()));
                }

                else if (protagonist.GetCurrentWeapon() != 0 && protagonist.GetAmountOfMissile() > 0) {
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
    application.imageAssets.bulletImage.loadFromFile("IMG/PlasmaBullet.png");
    application.imageAssets.rocketImage.loadFromFile("IMG/rocket1.png");
    application.imageAssets.smartRocketImage.loadFromFile("IMG/SmartRocket.png");
    application.imageAssets.enemyBulletImage.loadFromFile("IMG/RedPlasmaBullet.png");
    application.imageAssets.heroImage.loadFromFile("IMG/8888.png");
    application.imageAssets.easyEnemyImage.loadFromFile("IMG/EasyEnemyYellowThrust1.png");
    application.imageAssets.mediumEnemyImage.loadFromFile("IMG/MediumEnemyWithGreenThrust.png");
    application.imageAssets.strongEnemyImage.loadFromFile("IMG/StrongEnemyWithGreenThrust.png");
    application.imageAssets.asteroid.loadFromFile("IMG/Asteroids/strip_rock_type_D.png");
}

Object InitializePlayer(Application &application) {
    return application.map.GetObject("player");
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
//    auto new_end = std::remove_if(application.entities.begin(), application.entities.end(), IsNotAliveEntity);
//    application.entities.erase(new_end, application.entities.end());
    static float localTime = 0.f;
    for (std::list<Entity *>::iterator it = application.entities.begin(); it != application.entities.end(); ++it) {
        Entity *tmp = *it;
        if (IsNotAliveEntity(*it)) {
            it = application.entities.erase(it);
//            delete tmp;
        }
        if (0 >= application.amountOfEnemies) {
            if (tmp->name == "player") {
                it = application.entities.erase(it);
                printf("player was deleted\n");
            }
        }
        localTime += time_ms;
        AppendEnemiesBullets(application, tmp, protagonist, localTime);
        tmp->Update(time_ms, application.objects);
    }
}

bool IsShieldActive(const Application &application, const Player &protagonist) {
    return application.playerShieldIsActive && protagonist.GetShield() > 0;
}

bool IsEnemyProjectile(const string &name) {
    return (name == "EnemyBullet" || name == "EnemyRocket" || name == "EnemySmartRocket");
}

bool IsPlayerProjectile(const string &name) {
    return (name == "Bullet" || name == "Rocket");
}

bool IsReward(const string &name) {
    return (name == "HealthReward" || name == "ShieldReward");
}

bool IsEnemy(const string &name) {
    return (name == "easyEnemy" || name == "mediumEnemy" || name == "strongEnemy");
}

bool IsPlayer(const string &name) {
    return name == "player";
}

void DecreaseAmountOfEnemiesWhenTheyAreDying(int health, Application &application) {
    if (health <= 0 && application.amountOfEnemies > 0) {
        --application.amountOfEnemies;
    }
}

void SetPlayerHealth(Player &protagonist, int health) {
    protagonist.SetHealth(protagonist.GetHealth() + health);
}

void SetPlayerShield(Player &protagonist, int shield) {
    protagonist.SetShield(protagonist.GetShield() + shield);
}

void ProcessMeleeDamage(Entity *entity, Application &application, Player &protagonist) {

    if (IsEnemy(entity->name)) {

        entity->boost.x = 0;
        entity->boost.y = 0;
        entity->health -= (application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                           abs(static_cast<long>(entity->velocity.x + entity->velocity.y) / 2));

        if (protagonist.GetShield() > 0 && application.playerShieldIsActive) {
            protagonist.SetShield(protagonist.GetShield() -
                                  static_cast<int>((application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                                    abs(static_cast<long>(entity->velocity.x + entity->velocity.y) /
                                                        2))));
        }

        else {
            protagonist.SetHealth(protagonist.GetHealth() -
                                  static_cast<int>(application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                                   abs(static_cast<long>(entity->velocity.x + entity->velocity.y) /
                                                       2)));
        }

        application.gui.UpdateEnemy(static_cast<size_t>(entity->health), entity->name);
        DecreaseAmountOfEnemiesWhenTheyAreDying(entity->health, application);
    }

    else if (entity->name == "ShieldReward" && protagonist.GetShield() + 30 < protagonist.GetMAX_SHIELD()) {
        protagonist.SetShield(protagonist.GetShield() + 30);
        entity->alive = false;
    }

    else if (entity->name == "HealthReward" && protagonist.GetHealth() + 30 < protagonist.GetMAX_HP()) {
        protagonist.SetHealth(protagonist.GetHealth() + 30);
        entity->alive = false;
    }

}

void ProcessDistanceDamage(Entity *entity, Application &application, Player &protagonist) {

    if (entity->name == "EnemyBullet") {

        if (IsShieldActive(application, protagonist)) {
            SetPlayerShield(protagonist,
                            -static_cast<int>(application.enemiesHandler.easyEnemy.easyEnemyBullet.DAMAGE /
                                              2));
        }

        else {
            SetPlayerHealth(protagonist,
                            -static_cast<int>(application.enemiesHandler.easyEnemy.easyEnemyBullet.DAMAGE));
        }

        entity->alive = false;
    }

    else if (entity->name == "EnemyRocket") {

        if (IsShieldActive(application, protagonist)) {
            SetPlayerShield(protagonist,
                            -static_cast<int>(application.enemiesHandler.mediumEnemy.simpleRocket.DAMAGE /
                                              2));
        }

        else {
            SetPlayerHealth(protagonist,
                            -static_cast<int>(application.enemiesHandler.mediumEnemy.simpleRocket.DAMAGE));
        }

        entity->name = "explosion";
    }

    else if (entity->name == "EnemySmartRocket") {

        if (IsShieldActive(application, protagonist)) {
            SetPlayerShield(protagonist,
                            -static_cast<int>(application.enemiesHandler.hardEnemy.smartRocket.DAMAGE /
                                              2));
        }

        else {
            SetPlayerHealth(protagonist,
                            -static_cast<int>(application.enemiesHandler.hardEnemy.smartRocket.DAMAGE));
        }

        entity->name = "explosion";
    }
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

                    DecreaseAmountOfEnemiesWhenTheyAreDying(it->health, application);

                }
                ProcessAsteroidDamage(at, it, application, protagonist);
            }

        }
        if (it->RetRect().intersects(protagonist.RetRect())) {

            if (IsEnemyProjectile(it->name)) {
                ProcessDistanceDamage(it, application, protagonist);
            }

            else {
                ProcessMeleeDamage(it, application, protagonist);
            }

            application.gui.UpdateProtagonist(static_cast<size_t>(protagonist.GetHealth()),
                                              static_cast<size_t>(protagonist.GetShield()));
        }
    }
}

void ProcessAsteroidDamage(Entity *entity1, Entity *entity2, Application &application, Player &protagonist) {

    if (entity1->name == "Asteroid" && entity2->name != "Asteroid") {
        if (IsEnemyProjectile(entity2->name) || IsPlayerProjectile(entity2->name)) {
            entity2->alive = false;
            entity1->name = "explosion";
        }
        else if (!IsReward(entity2->name)) {
            if (IsEnemy(entity2->name)) {
                entity2->health -= 100;
            }
            else if (IsPlayer(entity2->name)) {
                protagonist.SetHealth(protagonist.GetHealth() - 50);
                protagonist.SetShield(protagonist.GetShield() - 50);
            }
            entity1->name = "explosion";
        }
    }

}

void AppendEnemies(Application &application) {

    application.enemiesContainer.easyOpponent = application.map.GetObjects("easyEnemy");
//    application.enemiesContainer.mediumOpponent = application.map.GetObjects("mediumEnemy");
    application.enemiesContainer.strongOpponent = application.map.GetObjects("hardEnemy");

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
        cout << "game over\n";
        window.close();
    }
}

void AppendAsteroids(size_t amount, Application &application) {
    for (size_t i = 0; i < amount; ++i) {
        application.entities.push_back(
                new Asteroid(application.imageAssets.asteroid,
                             {static_cast<float>(rand() % (mapSize[currentLevel].first - 20 + 1) + 20),
                              static_cast<float>(rand() % (mapSize[currentLevel].second - 10 + 1) + 10)},
                             {65, 64},
                             "Asteroid"));
    }
}

void Draw(Player &protagonist, Application &application) {
    application.window.clear();
    application.map.Draw(application.window);
    for (auto it : application.entities) {
        application.window.draw((it)->sprite);
    }
    if (protagonist.alive) {
        application.window.draw(protagonist.sprite);
    }
    if (application.playerShieldIsActive && protagonist.GetShield() > 0) {
        application.shield.Draw(application.window, protagonist.position);
    }
    application.gui.Draw(application.window, protagonist.GetCurrentWeapon(), protagonist.GetAmountOfMissile(),
                         application.amountOfEnemies);
    application.aim.Draw(application.window);
    //if (protagonist.GetState() == 0) {
    //application.thrust.Draw(application.window, protagonist.position, application.objects.playerRotation);
    //}
    application.window.display();
}

bool AllEnemiesDead(const Application &application) {
    return application.amountOfEnemies == 0;
}

void MainLoop(Application &application, Player &protagonist) {

    while (application.window.isOpen()) {
        GetMousePosition(application.window, application.playerPosition);
        float time_ms = RunTimer(application);
        ProcessEvents(protagonist, application);
        protagonist.rotation_GG(application.playerPosition);
        ProcessEntities(time_ms, application, protagonist);
        ProcessDamage(protagonist, application);
        CheckExistenceProtagonist(protagonist, application.window);
        application.window.setView(view);
        Draw(protagonist, application);
        if (AllEnemiesDead(application)) {
            printf("All enemies are dead\n");
            break;
        }
    }

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
    application.window.setFramerateLimit(60);
    application.window.setVerticalSyncEnabled(true);
    view.reset(
            sf::FloatRect(0, 0, application.parameters.WINDOW_SIZE.first, application.parameters.WINDOW_SIZE.second));
}


void Initialize(Application &application) {
    InitializeWindow(application);
    InitializeImages(application);
}

void SetLevel(Application &application, size_t level) {
    SetMapSize(application);

    application.map.LoadFromFile(application.mapInfo[level].first);

    AppendAsteroids(application.mapInfo[level].second, application);

    AppendEnemies(application);

}

void Run(Application &application, size_t level) {
    SetLevel(application, level);
    auto protagonist = CreatePlayer(application);
    MainLoop(application, protagonist);
}

void CloseWindowWhenItWasInterrupted(Application &application, const Event &event) {
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        application.window.close();
        printf("The window was closed");
    }
}

void DrawMenu(Application &application) {
    Event event;
    while (application.window.isOpen() && application.gameState == MENU) {
        while (application.window.pollEvent(event)) {
            CloseWindowWhenItWasInterrupted(application, event);
        }
        application.window.clear();
        application.menu.Draw(application.window, application.gameState);
        application.window.display();
    }
}

void StartGame(size_t level) {
    Application application;
    currentLevel = level;
    Initialize(application);
    printf("game\n");
    application.window.setMouseCursorVisible(false);
    Run(application, level);
}

