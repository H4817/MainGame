#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Bar.h"
#include "shield.h"
#include "Thrust.h"
#include "aim.h"

struct Application {
    bool playerShieldIsActive = false;
    const Vector2f MAP_WIDTH = {850, 2400};
    const Vector2f MAP_HEIGHT = {530, 2600};
    PlayerProperties playerProperties;
    Clock clock;
    Level lvl;
    sf::View view;
    std::list<Entity *> entities;
    LifeBar lifeBar;
    Shield shield;
    Thrust thrust;
    Aim aim;
   // Reward reward;
};

Application g_application;

struct PlayerPosition {
    Vector2f pos;
};

struct ImageAssets {
    Image heroImage;
    Image easyEnemyImage;
    Image bulletImage;
};


void getPlayerCoordinateForView(Vector2f position, PlayerProperties &playerProperties) {
    Vector2f centerPosition = {position.x, position.y};
    if (position.x < g_application.MAP_WIDTH.x) centerPosition.x = g_application.MAP_WIDTH.x;
    if (position.x > g_application.MAP_WIDTH.y) centerPosition.x = g_application.MAP_WIDTH.y;
    if (position.y < g_application.MAP_HEIGHT.x) centerPosition.y = g_application.MAP_HEIGHT.x;
    if (position.y > g_application.MAP_HEIGHT.y) centerPosition.y = g_application.MAP_HEIGHT.y;
    g_application.view.setCenter(centerPosition.x, centerPosition.y);
}

float RunTimer() {
    float time_ms = g_application.clock.getElapsedTime().asMicroseconds();
    g_application.clock.restart();
    time_ms = (float) (time_ms * 0.001);
    return time_ms;
}

void ProcessEvents(RenderWindow &window, Player &protagonist, ImageAssets &imagesStruct, PlayerPosition &playerPosition,
                   PlayerBullet &playerBullet, MapObjects &objects) {
    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            g_application.entities.push_back(
                    new Bullet(imagesStruct.bulletImage, objects, g_application.lvl, protagonist.position,
                               playerBullet.SIZE, playerPosition.pos, "Bullet"));
        }
        if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::F) {
            g_application.playerShieldIsActive = !g_application.playerShieldIsActive;
        }
    }
}

void GetMousePosition(RenderWindow &window, PlayerPosition &playerPosition) {
    Vector2i pixelPos = Mouse::getPosition(window);
    playerPosition.pos = window.mapPixelToCoords(pixelPos);
}

void InitializeImages(ImageAssets &imagesStruct) {
    g_application.lvl.LoadFromFile("Assets/map.tmx");
    imagesStruct.bulletImage.loadFromFile("IMG/PlasmaBullet.png");
    imagesStruct.heroImage.loadFromFile("IMG/888.png");
    imagesStruct.easyEnemyImage.loadFromFile("IMG/EasyEnemy.png");
}

Object InitializePlayer() {
    Object player = g_application.lvl.GetObject("player");
    return player;
}

bool IsAliveEntity(Entity *entity) {
    return !entity->alive;
}

void ProcessEntities(float &time_ms, MapObjects &objects) {
    auto new_end = std::remove_if(g_application.entities.begin(), g_application.entities.end(), IsAliveEntity);
    g_application.entities.erase(new_end, g_application.entities.end());
    for (auto it : g_application.entities) {
        it->update(time_ms, objects);
    }
}

void ProcessDamage(Player &protagonist, PlayerBullet &playerBullet, EasyEnemy &easyEnemy,
                   PlayerProperties &playerProperties) {
    for (auto it : g_application.entities) {
        for (auto at : g_application.entities) {
            if ((it)->getRect().intersects((at)->getRect()) &&
                (((at)->name == "Bullet") && ((it)->name == "easyEnemy"))) {
                it->healthEasyEnemy -= playerBullet.DAMAGE;
                (at)->alive = false;
                g_application.lifeBar.updateEnemy(it->healthEasyEnemy);
            }
        }
        if ((it)->getRect().intersects(protagonist.getRect())) {
            if ((it)->name == "easyEnemy") {
                (it)->boost.x -= it->boost.x;
                (it)->boost.y -= it->boost.y;
                if (playerProperties.shield > 0 && g_application.playerShieldIsActive) {
                    playerProperties.shield -= easyEnemy.DAMAGE;
                }
                else {
                    protagonist.health -= easyEnemy.DAMAGE;
                }
                g_application.lifeBar.updateSelf(protagonist.health, playerProperties.shield);
            }
            else if (it->name == "ShieldReward") {
                playerProperties.shield += 30;
                it->alive = false;
                g_application.lifeBar.updateSelf(protagonist.health, playerProperties.shield);
            }
            else if (it->name == "HealthReward") {
                protagonist.health += 30;
                it->alive = false;
                g_application.lifeBar.updateSelf(protagonist.health, playerProperties.shield);
            }
        }
    }
}

void AppendEnemies(vector<Object> &easyOpponent, ImageAssets &imagesStruct, EasyEnemy &easyEnemy,
                   MapObjects &objects, PlayerPosition &playerPosition, Player &protagonist) {
    for (int i = 0; i < easyOpponent.size(); i++) {
        g_application.entities.push_back(new Enemy(imagesStruct.easyEnemyImage, objects, g_application.lvl,
                                                   {easyOpponent[i].rect.left, easyOpponent[i].rect.top},
                                                   easyEnemy.SIZE, g_application.playerProperties.position, "easyEnemy"));
    }
}


void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window) {
    if (!protagonist.alive)
        window.close();
}

void Draw(RenderWindow &window, Player &protagonist, PlayerProperties &playerProperties) {
    window.clear();
    g_application.lvl.Draw(window);
    for (auto it : g_application.entities) {
        window.draw((it)->sprite);
    }
    window.draw(protagonist.sprite);
    if (g_application.playerShieldIsActive && playerProperties.shield > 0) {
        g_application.shield.Draw(window, protagonist.position);
    }
    g_application.lifeBar.draw(window);
    if (protagonist.isMOVE) {
        g_application.thrust.Draw(window, protagonist.position, protagonist.rotation);
    }
   // g_application.reward.Draw(window);
    g_application.aim.Draw(window);
    //window.draw((&g_application)->enemy->shieldReward);
    window.display();
}


int main() {
    EasyEnemy easyEnemy;
    PlayerBullet playerBullet;
    PlayerProperties playerProperties;
    Parameters parameters;
    MapObjects objects;
    sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y), "Game");
    window.setMouseCursorVisible(false);
    g_application.view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y));
    ImageAssets imageAssets;
    PlayerPosition playerPosition;
    InitializeImages(imageAssets);
    Object player = InitializePlayer();
    std::vector<Object> easyOpponent = g_application.lvl.GetObjects("easyEnemy");
    Player protagonist(imageAssets.heroImage, objects, g_application.lvl, {player.rect.left, player.rect.top},
                       playerProperties.SIZE, "player");
    AppendEnemies(easyOpponent, imageAssets, easyEnemy, objects, playerPosition, protagonist);
    while (window.isOpen()) {
        GetMousePosition(window, playerPosition);
        float time_ms = RunTimer();
        ProcessEvents(window, protagonist, imageAssets, playerPosition, playerBullet, objects);
        protagonist.rotation_GG(playerPosition.pos);
        protagonist.update(time_ms, objects);
        ProcessEntities(time_ms, objects);
        ProcessDamage(protagonist, playerBullet, easyEnemy, playerProperties);
        CheckExistenceProtagonist(protagonist, window);
        window.setView(g_application.view);
        Draw(window, protagonist, playerProperties);
    }
    return 0;
}