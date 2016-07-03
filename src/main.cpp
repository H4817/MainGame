#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Bar.h"
#include "shield.h"
#include "aim.h"

namespace {
    const Vector2f MAP_WIDTH = {850, 2370};
    const Vector2f MAP_HEIGHT = {530, 2600};
    sf::View view;
}

struct Application {
    bool playerShieldIsActive = false;
    Clock clock;
    Level lvl;
    std::list<Entity *> entities;
    Bar bar;
    Shield shield;
    Aim aim;
};

struct PlayerPosition {
    Vector2f pos;
};

struct ImageAssets {
    Image heroImage;
    Image easyEnemyImage;
    Image bulletImage;
    Image enemyBulletImage;
};

void getPlayerCoordinateForView(Vector2f position, PlayerProperties &playerProperties) {
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

void ProcessEvents(RenderWindow &window, Player &protagonist, ImageAssets &imagesStruct, PlayerPosition &playerPosition,
                   PlayerBullet &playerBullet, MapObjects &objects, PlayerProperties &playerProperties,
                   Application &application) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed || event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::R && playerProperties.shield > 0) {
            application.entities.push_back(
                    new Bullet(imagesStruct.bulletImage, objects, application.lvl, protagonist.position,
                               playerBullet.SIZE, playerPosition.pos, "Bullet"));
            playerProperties.shield -= 2;
            application.bar.UpdateProtagonist(protagonist.health, playerProperties.shield);
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

void InitializeImages(ImageAssets &imagesStruct, Application &application) {
    application.lvl.LoadFromFile("Assets/map1.tmx");
    imagesStruct.bulletImage.loadFromFile("IMG/PlasmaBullet.png");
    imagesStruct.enemyBulletImage.loadFromFile("IMG/RedPlasmaBullet.png");
    imagesStruct.heroImage.loadFromFile("IMG/8888.png");
    imagesStruct.easyEnemyImage.loadFromFile("IMG/EasyEnemyYellowThrust1.png");
}

Object InitializePlayer(Application &application) {
    Object player = application.lvl.GetObject("player");
    return player;
}

bool IsAliveEntity(Entity *entity) {
    return !entity->alive;
}

void ProcessEntities(float &time_ms, MapObjects &objects, Application &application, ImageAssets &imagesStruct, Player &protagonist) {
    auto new_end = std::remove_if(application.entities.begin(), application.entities.end(), IsAliveEntity);
    application.entities.erase(new_end, application.entities.end());
    for (auto it : application.entities) {
        if (it->name == "easyEnemy")
            application.entities.push_back(
                    new Bullet(imagesStruct.enemyBulletImage, objects, application.lvl, it->position,
                               {54, 25}, protagonist.position, "EnemyBullet"));
        it->Update(time_ms, objects);
    }
}

void ProcessDamage(Player &protagonist, PlayerBullet &playerBullet, EasyEnemy &easyEnemy,
                   PlayerProperties &playerProperties, Application &application) {
    for (auto it : application.entities) {
        for (auto at : application.entities) {
            if (it->RetRect().intersects(at->RetRect()) &&
                ((at->name == "Bullet") && (it->name == "easyEnemy"))) {
                it->healthEasyEnemy -= playerBullet.DAMAGE;
                at->alive = false;
                application.bar.UpdateEnemy(it->healthEasyEnemy);
            }
        }
        if (it->RetRect().intersects(protagonist.RetRect())) {
            if (it->name == "EnemyBullet") {
                if (playerProperties.shield > 0 && application.playerShieldIsActive) {
                    playerProperties.shield -= 0.00000001;
                }
                else {
                    protagonist.health -= 0.0000001;
                }
            }
            if (it->name == "easyEnemy") {
                it->boost.x = 0;
                it->boost.y = 0;
                it->healthEasyEnemy -= (easyEnemy.COLLISION_DAMAGE +
                                        abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                if (playerProperties.shield > 0 && application.playerShieldIsActive) {
                    playerProperties.shield -= (easyEnemy.COLLISION_DAMAGE +
                                                abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                }
                else {
                    protagonist.health -= (easyEnemy.COLLISION_DAMAGE +
                                           abs(static_cast<long>(it->velocity.x + it->velocity.y) / 2));
                }
                application.bar.UpdateEnemy(it->healthEasyEnemy);
            }
            else if (it->name == "ShieldReward") {
                playerProperties.shield += 30;
                it->alive = false;
            }
            else if (it->name == "HealthReward") {
                protagonist.health += 30;
                it->alive = false;
            }
            application.bar.UpdateProtagonist(protagonist.health, playerProperties.shield);
        }
    }
}

void AppendEnemies(vector<Object> &easyOpponent, ImageAssets &imagesStruct, EasyEnemy &easyEnemy,
                   MapObjects &objects, PlayerPosition &playerPosition, Player &protagonist, Application &application) {
    for (int i = 0; i < easyOpponent.size(); i++) {
        application.entities.push_back(new Enemy(imagesStruct.easyEnemyImage, objects, application.lvl,
                                                 {easyOpponent[i].rect.left, easyOpponent[i].rect.top},
                                                 easyEnemy.SIZE, playerPosition.pos, "easyEnemy"));
    }
}

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window) {
    if (!protagonist.alive)
        window.close();
}

void Draw(RenderWindow &window, Player &protagonist, PlayerProperties &playerProperties, Application &application) {
    window.clear();
    application.lvl.Draw(window);
    for (auto it : application.entities) {
        window.draw((it)->sprite);
    }
    window.draw(protagonist.sprite);
    if (application.playerShieldIsActive && playerProperties.shield > 0) {
        application.shield.Draw(window, protagonist.position);
    }
    application.bar.Draw(window);
    application.aim.Draw(window);
    window.display();
}

int main() {
    EasyEnemy easyEnemy;
    PlayerBullet playerBullet;
    PlayerProperties playerProperties;
    Parameters parameters;
    MapObjects objects;
    Application application;
    sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE.first, parameters.WINDOW_SIZE.second), "Game");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE.first, parameters.WINDOW_SIZE.second));
    ImageAssets imageAssets;
    PlayerPosition playerPosition;
    InitializeImages(imageAssets, application);
    Object player = InitializePlayer(application);
    std::vector<Object> easyOpponent = application.lvl.GetObjects("easyEnemy");
    Player protagonist(imageAssets.heroImage, objects, application.lvl, {player.rect.left, player.rect.top},
                       playerProperties.SIZE, "player");
    AppendEnemies(easyOpponent, imageAssets, easyEnemy, objects, playerPosition, protagonist, application);
    while (window.isOpen()) {
        GetMousePosition(window, playerPosition);
        float time_ms = RunTimer(application);
        ProcessEvents(window, protagonist, imageAssets, playerPosition, playerBullet, objects, playerProperties,
                      application);
        protagonist.rotation_GG(playerPosition.pos);
        protagonist.Update(time_ms, objects);
        ProcessEntities(time_ms, objects, application, imageAssets, protagonist);
        ProcessDamage(protagonist, playerBullet, easyEnemy, playerProperties, application);
        CheckExistenceProtagonist(protagonist, window);
        window.setView(view);
        Draw(window, protagonist, playerProperties, application);
    }
    return 0;
}
