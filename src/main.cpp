#include "Player.h"
#include "Bullet.h"
#include "Enemies.h"
#include "Bar.h"
#include "shield.h"
#include "aim.h"

namespace {
    const Vector2f MAP_WIDTH = {850, 2370};
    const Vector2f MAP_HEIGHT = {530, 2600};
    sf::View view;
}

struct EnemiesContainer {
    std::vector<Object> easyOpponent;
    std::vector<Object> mediumOpponent;
};

struct ImageAssets {
    Image heroImage;
    Image easyEnemyImage;
    Image mediumEnemyImage;
    Image bulletImage;
    Image rocketImage;
    Image smartRocketImage;
    Image enemyBulletImage;
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
};

struct PlayerPosition {
    Vector2f pos;
};


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
    time_ms = static_cast<float> (time_ms * 0.001);
    return time_ms;
}

void ProcessEvents(RenderWindow &window, Player &protagonist, PlayerPosition &playerPosition,
                   Application &application) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed || event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::R &&
            application.playerProperties.shield > 0) {
            application.entities.push_back(
                    new Bullet(application.imageAssets.bulletImage, application.objects, application.lvl,
                               protagonist.position,
                               application.playerProperties.playerBullet.SIZE, playerPosition.pos, "Bullet"));
            application.playerProperties.shield -= 2;
            application.bar.UpdateProtagonist(protagonist.health, application.playerProperties.shield);
        }
        if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::F) {
            application.playerShieldIsActive = !application.playerShieldIsActive;
        }
    }
}

void GetMousePosition(RenderWindow &window, PlayerPosition &playerPosition) {
    Vector2i pixelPos = Mouse::getPosition(window);
    playerPosition.pos = window.mapPixelToCoords(pixelPos);
}

void InitializeImages(Application &application) {
    application.lvl.LoadFromFile("Assets/map1.tmx");
    application.imageAssets.bulletImage.loadFromFile("IMG/PlasmaBullet.png");
    application.imageAssets.rocketImage.loadFromFile("IMG/rocket1.png");
    application.imageAssets.smartRocketImage.loadFromFile("IMG/SmartRocket.png");
    application.imageAssets.enemyBulletImage.loadFromFile("IMG/RedPlasmaBullet.png");
    application.imageAssets.heroImage.loadFromFile("IMG/8888.png");
    application.imageAssets.easyEnemyImage.loadFromFile("IMG/EasyEnemyYellowThrust1.png");
    application.imageAssets.mediumEnemyImage.loadFromFile("IMG/MediumEnemyWithGreenThrust.png");
}

Object InitializePlayer(Application &application) {
    Object player = application.lvl.GetObject("player");
    return player;
}

bool IsAliveEntity(Entity *entity) {
    return !entity->alive;
}

bool IsAggro(const Vector2f &protagonistPosition, const Vector2f &enemyPosition, const size_t &distance) {
    return ((abs(protagonistPosition.x - enemyPosition.x)) < distance &&
            (abs(protagonistPosition.y - enemyPosition.y)) < distance);
}

void AppendEnemiesBullets(Application &application, Entity *it, Player &protagonist, sf::Time elapsed) {
    if ((it->name == "easyEnemy") &&
        IsAggro(protagonist.position, it->position, application.enemiesHandler.easyEnemy.AGGRO_DISTANCE) &&
        elapsed.asMicroseconds() > 30) {
        application.entities.push_back(
                new Bullet(application.imageAssets.enemyBulletImage, application.objects, application.lvl, it->position,
                           application.enemiesHandler.easyEnemy.easyEnemyBullet.SIZE,
                           protagonist.position,
                           "EnemyBullet"));
    }
    else if ((it->name == "mediumEnemy") &&
             IsAggro(protagonist.position, it->position, application.enemiesHandler.mediumEnemy.AGGRO_DISTANCE) &&
             elapsed.asMicroseconds() > 40) {
        application.entities.push_back(
                new SmartRocket(application.imageAssets.smartRocketImage, application.objects, application.lvl,
                                it->position,
                                application.enemiesHandler.mediumEnemy.smartRocket.SIZE,
                                protagonist.position, "EnemyRocket"));
    }
}

void ProcessEntities(float &time_ms, Application &application, Player &protagonist) {
    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    auto new_end = std::remove_if(application.entities.begin(), application.entities.end(), IsAliveEntity);
    application.entities.erase(new_end, application.entities.end());
    for (auto it : application.entities) {
        elapsed = clock.getElapsedTime();
        AppendEnemiesBullets(application, it, protagonist, elapsed);
        it->Update(time_ms, application.objects);
    }
}

bool IsShieldActive(const Application &application) {
    return application.playerShieldIsActive && application.playerProperties.shield > 0;
}

void ProcessDamage(Player &protagonist, Application &application) {
    for (auto it : application.entities) {
        for (auto at : application.entities) {
            if (it->RetRect().intersects(at->RetRect()) &&
                ((at->name == "Bullet") && (it->name == "easyEnemy" || it->name == "mediumEnemy"))) {
                it->enemyHealth -= application.playerProperties.playerBullet.DAMAGE;
                at->alive = false;
                application.bar.UpdateEnemy(it->enemyHealth);
            }
        }
        if (it->RetRect().intersects(protagonist.RetRect())) {
            if (it->name == "EnemyBullet") {
                if (IsShieldActive(application)) {
                    application.playerProperties.shield -=
                            application.enemiesHandler.easyEnemy.easyEnemyBullet.DAMAGE / 2;
                }
                else {
                    protagonist.health -= application.enemiesHandler.easyEnemy.easyEnemyBullet.DAMAGE;
                }
                it->alive = false;
            }
            else if (it->name == "EnemyRocket") {
                if (IsShieldActive(application)) {
                    application.playerProperties.shield -=
                            application.enemiesHandler.mediumEnemy.smartRocket.DAMAGE / 2;
                }
                else {
                    protagonist.health -= application.enemiesHandler.mediumEnemy.smartRocket.DAMAGE;
                }
                it->name = "explosion";
            }
            else if (it->name == "easyEnemy" || it->name == "mediumEnemy") {
                it->boost.x = 0;
                it->boost.y = 0;
                it->enemyHealth -= (application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                    abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                if (application.playerProperties.shield > 0 && application.playerShieldIsActive) {
                    application.playerProperties.shield -= (application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                                            abs(static_cast<long>(it->velocity.x + it->velocity.y) /
                                                                2));
                }
                else {
                    protagonist.health -= (application.enemiesHandler.easyEnemy.COLLISION_DAMAGE +
                                           abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                }
                application.bar.UpdateEnemy(it->enemyHealth);
            }
            else if (it->name == "ShieldReward") {
                application.playerProperties.shield += 30;
                it->alive = false;
            }
            else if (it->name == "HealthReward") {
                protagonist.health += 30;
                it->alive = false;
            }
            application.bar.UpdateProtagonist(protagonist.health, application.playerProperties.shield);
        }
    }
}

void AppendEnemies(PlayerPosition &playerPosition, Player &protagonist, Application &application) {
    for (int i = 0; i < application.enemiesContainer.easyOpponent.size(); i++) {
        application.entities.push_back(
                new CEasyEnemy(application.imageAssets.easyEnemyImage, application.objects, application.lvl,
                               {application.enemiesContainer.easyOpponent[i].rect.left,
                                application.enemiesContainer.easyOpponent[i].rect.top},
                               application.enemiesHandler.easyEnemy.SIZE, playerPosition.pos,
                               "easyEnemy"));
    }
    for (int i = 0; i < application.enemiesContainer.mediumOpponent.size(); i++) {
        application.entities.push_back(
                new CMediumEnemy(application.imageAssets.mediumEnemyImage, application.objects, application.lvl,
                                 {application.enemiesContainer.mediumOpponent[i].rect.left,
                                  application.enemiesContainer.mediumOpponent[i].rect.top},
                                 application.enemiesHandler.mediumEnemy.SIZE, playerPosition.pos,
                                 "mediumEnemy"));
    }
}

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window) {
    if (!protagonist.alive)
        window.close();
}

void Draw(RenderWindow &window, Player &protagonist, Application &application) {
    window.clear();
    application.lvl.Draw(window);
    for (auto it : application.entities) {
        window.draw((it)->sprite);
    }
    window.draw(protagonist.sprite);
    if (application.playerShieldIsActive && application.playerProperties.shield > 0) {
        application.shield.Draw(window, protagonist.position);
    }
    application.bar.Draw(window);
    application.aim.Draw(window);
    window.display();
}

int main() {
    Parameters parameters;
    Application application;
    sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE.first, parameters.WINDOW_SIZE.second), "Game");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE.first, parameters.WINDOW_SIZE.second));
    PlayerPosition playerPosition;
    InitializeImages(application);
    Object player = InitializePlayer(application);
    application.enemiesContainer.easyOpponent = application.lvl.GetObjects("easyEnemy");
    application.enemiesContainer.mediumOpponent = application.lvl.GetObjects("mediumEnemy");
    Player protagonist(application.imageAssets.heroImage, application.objects, application.lvl,
                       {player.rect.left, player.rect.top},
                       application.playerProperties.SIZE, "player");
    AppendEnemies(playerPosition, protagonist, application);
    while (window.isOpen()) {
        GetMousePosition(window, playerPosition);
        float time_ms = RunTimer(application);
        ProcessEvents(window, protagonist, playerPosition, application);
        protagonist.rotation_GG(playerPosition.pos);
        protagonist.Update(time_ms, application.objects);
        ProcessEntities(time_ms, application, protagonist);
        ProcessDamage(protagonist, application);
        CheckExistenceProtagonist(protagonist, window);
        window.setView(view);
        Draw(window, protagonist, application);
    }
    return 0;
}
