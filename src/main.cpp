#include <SFML/Graphics.hpp>
#include <iostream>
#include "view.h"
#include "level.h"
#include "Classes.h"


using namespace sf;


int main() {
	sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y), "Game");
	view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y));

	Level lvl;
	lvl.LoadFromFile("Assets/map.tmx");

	Object player = lvl.GetObject("player");

	std::list<Entity*> entities;
	std::list<Entity*>::iterator it;

	std::vector<Object> easyOpponent = lvl.GetObjects("easyEnemy");

	Image heroImage, easyEnemyImage, bulletImage;
	bulletImage.loadFromFile("IMG/projectile_bolt_blue_single.png");
	heroImage.loadFromFile("IMG/PlayerShip.png");
	easyEnemyImage.loadFromFile("IMG/EasyEnemy.png");
	std::cout << player.rect.left << player.rect.top;
	Player protagonist(heroImage, lvl, player.rect.left, player.rect.top, playerStruct.WIDTH, playerStruct.HEIGHT, "Player");
	Clock clock;

	for (int i = 0; i < easyOpponent.size(); i++)
		entities.push_back(new Enemy(easyEnemyImage, lvl, easyOpponent[i].rect.left, easyOpponent[i].rect.top, easyEnemyStruct.WIDTH, easyEnemyStruct.HEIGHT, "easyEnemy"));

	while (window.isOpen()) {
		std::list<Entity*>::iterator at;
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == Mouse::Left) {
				entities.push_back(new Bullet(bulletImage, lvl, protagonist.x, protagonist.y, playerBulletStruct.WIDTH, playerBulletStruct.HEIGHT, pos.x, pos.y, "Bullet"));
			}
		}
		protagonist.rotation_GG(pos);
		protagonist.update(time);
		for (it = entities.begin(); it != entities.end();) {
			Entity *projectile = *it;
			projectile->update(time);
			if (!projectile->life) {
				it = entities.erase(it);
				delete projectile;
			}
			else it++;
		}
		for (it = entities.begin(); it != entities.end(); it++) {
			for (at = entities.begin(); at != entities.end(); at++) {
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
		if (!protagonist.life)
			window.close();
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite);
		}
		window.draw(protagonist.sprite);
		window.display();
	}
	return 0;
}