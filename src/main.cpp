#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.h"
#include "Classes.h"


using namespace sf;



struct Application {
	Clock clock;
	Level lvl;
	sf::View view;
	std::list<Entity*> entities;
	std::list<Entity*>::iterator it;
};

struct PlayerPosition {
	Vector2i pixelPos;
	Vector2f pos;
};

struct ImagesStruct {
	Image heroImage, easyEnemyImage;
	Image bulletImage;
};



void getPlayerCoordinateForView(float x, float y, Application & application) {
	float tempX = x; float tempY = y;

	if (x < 685) tempX = 685;
	if (x > 1325) tempX = 1325;
	if (y < 380) tempY = 380;
	if (y > 1650) tempY = 1650;

	application.view.setCenter(tempX, tempY);

}


float RunTimer(Application & application) {
	float time = application.clock.getElapsedTime().asMicroseconds();
	application.clock.restart();
	time = time / 800;
	return time;
}

void ProcessEvents(RenderWindow & window, Player & protagonist, ImagesStruct & imagesStruct, PlayerPosition & playerPosition, Application & application) {
	sf::Event event;
	while (window.pollEvent(event))	{
		if (event.type == Event::Closed) {
			window.close();
		}
		if (event.key.code == Mouse::Left) {
			application.entities.push_back(new Bullet(imagesStruct.bulletImage, application.lvl, protagonist.x, protagonist.y, playerBulletStruct.WIDTH, playerBulletStruct.HEIGHT, playerPosition.pos.x, playerPosition.pos.y, "Bullet"));
		}
	}
}

void GetMousePosition(RenderWindow & window, PlayerPosition & playerPosition) {
	playerPosition.pixelPos = Mouse::getPosition(window);
	playerPosition.pos = window.mapPixelToCoords(playerPosition.pixelPos);
}

void InitializeImages(ImagesStruct & imagesStruct, Application & application) {
	application.lvl.LoadFromFile("Assets/map.tmx");
	imagesStruct.bulletImage.loadFromFile("IMG/projectile_bolt_blue_single.png");
	imagesStruct.heroImage.loadFromFile("IMG/PlayerShip.png");
	imagesStruct.easyEnemyImage.loadFromFile("IMG/EasyEnemy.png");
}

Object InitializePlayer(Application & application) {
	Object player = application.lvl.GetObject("player");
	return player;
}

void ProcessEntities(float & time, Application & application) {
	for (application.it = application.entities.begin(); application.it != application.entities.end();) {
		Entity *entity = *application.it;
		entity->update(time);
		if (!entity->life) {
			application.it = application.entities.erase(application.it);
			delete entity;
		}
		else application.it++;
	}
}

void ProcessDamage(Player & protagonist, Application & application) {
	for (auto it = application.entities.begin(); it != application.entities.end(); ++it) {
		for (auto at = application.entities.begin(); at != application.entities.end(); ++at) {
			if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && ((*it)->name == "easyEnemy"))) {
				(*it)->health -= playerBulletStruct.DAMAGE;
				(*at)->life = false;
			}
		}
		if ((*it)->getRect().intersects(protagonist.getRect())) {
			if ((*it)->name == "easyEnemy") {
				(*it)->dx = 0;
				protagonist.health -= easyEnemyStruct.DAMAGE;
			}
		}
	}
}

void AppendEnemies(std::vector<Object> & easyOpponent, ImagesStruct & imagesStruct, Application & application) {
	for (int i = 0; i < easyOpponent.size(); i++)
		application.entities.push_back(new Enemy(imagesStruct.easyEnemyImage, application.lvl, easyOpponent[i].rect.left, easyOpponent[i].rect.top, easyEnemyStruct.WIDTH, easyEnemyStruct.HEIGHT, "easyEnemy"));
}

void CheckExistenceProtagonist(Player &protagonist, RenderWindow &window) {
	if (!protagonist.life)
		window.close();
}

void Draw(RenderWindow &window, Player & protagonist, Application & application) {
	window.clear();
	application.lvl.Draw(window);
	for (application.it = application.entities.begin(); application.it != application.entities.end(); application.it++) {
		window.draw((*application.it)->sprite);
	}
	window.draw(protagonist.sprite);
	window.display();
}



int main() {
	sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y), "Game");
	Application application;
	application.view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y));
	ImagesStruct imagesStruct;
	PlayerPosition playerPosition;
	InitializeImages(imagesStruct, application);
	Object player = InitializePlayer(application);
	std::vector<Object> easyOpponent = application.lvl.GetObjects("easyEnemy");
	Player protagonist(imagesStruct.heroImage, application.lvl, player.rect.left, player.rect.top, playerStruct.WIDTH, playerStruct.HEIGHT, "Player");
	AppendEnemies(easyOpponent, imagesStruct, application);
	while (window.isOpen()) {
		GetMousePosition(window, playerPosition);
		float time = RunTimer(application);
		ProcessEvents(window, protagonist, imagesStruct, playerPosition, application);
		protagonist.rotation_GG(playerPosition.pos);
		protagonist.update(time);
		ProcessEntities(time, application);
		ProcessDamage(protagonist, application);
		CheckExistenceProtagonist(protagonist, window);
		window.setView(application.view);
		Draw(window, protagonist, application);
	}
	return 0;
}