#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.h"
#include "Classes.h"


using namespace sf;



struct Application {
	const Vector2f MAP_WIDTH = {850, 2400};
	const Vector2f MAP_HEIGHT = {530, 2600};
	Clock clock;
	Level lvl;
	sf::View view;
	std::list<Entity*> entities;
} application;

struct PlayerPosition {
	Vector2f pos;
};

struct ImageAssets {
	Image heroImage, easyEnemyImage;
	Image bulletImage;
};


void getPlayerCoordinateForView(Vector2f position) {
	Vector2f centerPosition = {position.x, position.y};
	if (position.x < application.MAP_WIDTH.x) centerPosition.x = application.MAP_WIDTH.x;
	if (position.x > application.MAP_WIDTH.y) centerPosition.x = application.MAP_WIDTH.y;
	if (position.y < application.MAP_HEIGHT.x) centerPosition.y = application.MAP_HEIGHT.x;
	if (position.y > application.MAP_HEIGHT.y) centerPosition.y = application.MAP_HEIGHT.y;
	application.view.setCenter(centerPosition.x, centerPosition.y);
}

float RunTimer() {
	float time = application.clock.getElapsedTime().asMicroseconds();
	application.clock.restart();
	time = time / 800;
	return time;
}

void ProcessEvents(RenderWindow & window, Player & protagonist, ImageAssets & imagesStruct, PlayerPosition & playerPosition) {
	sf::Event event;
	while (window.pollEvent(event))	{
		if (event.type == Event::Closed) {
			window.close();
		}
		if (event.key.code == Mouse::Left) {
			application.entities.push_back(new Bullet(imagesStruct.bulletImage, application.lvl, protagonist.position, playerBulletStruct.SIZE, playerPosition.pos, "Bullet"));
		}
	}
}

void GetMousePosition(RenderWindow & window, PlayerPosition & playerPosition) {
	Vector2i pixelPos = Mouse::getPosition(window);
	playerPosition.pos = window.mapPixelToCoords(pixelPos);
}

void InitializeImages(ImageAssets & imagesStruct) {
	application.lvl.LoadFromFile("Assets/map.tmx");
	imagesStruct.bulletImage.loadFromFile("IMG/projectile_bolt_blue_single.png");
	imagesStruct.heroImage.loadFromFile("IMG/PlayerShip.png");
	imagesStruct.easyEnemyImage.loadFromFile("IMG/EasyEnemy.png");
}

Object InitializePlayer() {
	Object player = application.lvl.GetObject("player");
	return player;
}

bool IsAliveEntity(Entity *entity) {
	return !entity->alive;
}

void ProcessEntities(float & time) {
	auto new_end = std::remove_if(application.entities.begin(), application.entities.end(), IsAliveEntity);
	application.entities.erase(new_end, application.entities.end());
	for (auto it : application.entities) {
		it->update(time);
	}
}

void ProcessDamage(Player & protagonist) {
	for (auto it : application.entities) {
		for (auto at : application.entities) {
			if ((it)->getRect().intersects((at)->getRect()) && (((at)->name == "Bullet") && ((it)->name == "easyEnemy"))) {
				(it)->health -= playerBulletStruct.DAMAGE;
				(at)->alive = false;
			}
		}
		if ((it)->getRect().intersects(protagonist.getRect())) {
			if ((it)->name == "easyEnemy") {
				(it)->boost.x = 0;
				protagonist.health -= easyEnemyStruct.DAMAGE;
			}
		}
	}
}

void AppendEnemies(std::vector<Object> & easyOpponent, ImageAssets & imagesStruct) {
	for (int i = 0; i < easyOpponent.size(); i++) {
		application.entities.push_back(new Enemy(imagesStruct.easyEnemyImage, application.lvl, {easyOpponent[i].rect.left, easyOpponent[i].rect.top}, {easyEnemyStruct.WIDTH, easyEnemyStruct.HEIGHT}, "easyEnemy"));
	}
}

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window) {
	if (!protagonist.alive)
		window.close();
}

void Draw(RenderWindow &window, Player & protagonist) {
	window.clear();
	application.lvl.Draw(window);
	for (auto it : application.entities) {
		window.draw((it)->sprite);
	}
	window.draw(protagonist.sprite);
	window.display();
}


int main() {
	sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y), "Game");
	application.view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y));
	ImageAssets imageAssets;
	PlayerPosition playerPosition;
	InitializeImages(imageAssets);
	Object player = InitializePlayer();
	std::vector<Object> easyOpponent = application.lvl.GetObjects("easyEnemy");
	Player protagonist(imageAssets.heroImage, application.lvl, {player.rect.left, player.rect.top}, playerStruct.SIZE, "Player");
	AppendEnemies(easyOpponent, imageAssets);
	while (window.isOpen()) {
		GetMousePosition(window, playerPosition);
		float time = RunTimer();
		ProcessEvents(window, protagonist, imageAssets, playerPosition);
		protagonist.rotation_GG(playerPosition.pos);
		protagonist.update(time);
		ProcessEntities(time);
		ProcessDamage(protagonist);
		CheckExistenceProtagonist(protagonist, window);
		window.setView(application.view);
		Draw(window, protagonist);
	}
	return 0;
}