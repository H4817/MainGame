#include <SFML/Graphics.hpp>
#include <iostream>
#include "view.h"
#include "level.h"
#include "Classes.h"

//branch dev

using namespace sf;

int main(){
	sf::RenderWindow window(sf::VideoMode(parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y), "Game");
	view.reset(sf::FloatRect(0, 0, parameters.WINDOW_SIZE_X, parameters.WINDOW_SIZE_Y));

	Level lvl;
	lvl.LoadFromFile("map.tmx");

	Object player = lvl.GetObject("player");

	std::list<Entity*> entities;
	std::list<Entity*>::iterator it;

	std::vector<Object> e = lvl.GetObjects("easyEnemy");

	Image heroImage, easyEnemyImage, bulletImage;
	bulletImage.loadFromFile("IMG/projectile_bolt_blue_single.png");
	heroImage.loadFromFile("IMG/PlayerShip.png");
	easyEnemyImage.loadFromFile("IMG/EasyEnemy.png");
	std::cout << player.rect.left << player.rect.top;
	Player p(heroImage, lvl, player.rect.left, player.rect.top, 91, 54, "Player");
	Clock clock;

	for (int i = 0; i < e.size(); i++)
		entities.push_back(new Enemy(easyEnemyImage, lvl, e[i].rect.left, e[i].rect.top, easyEnemyStruct.WIDTH, easyEnemyStruct.HEIGHT, "easyEnemy"));

	while (window.isOpen()){
		std::list<Entity*>::iterator at;
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == Mouse::Left){
				entities.push_back(new Bullet(bulletImage, lvl, p.x, p.y, playerBulletStruct.WIDTH, playerBulletStruct.HEIGHT, pos.x, pos.y, "Bullet"));
			}
		}
		p.rotation_GG(pos);
		p.update(time);
		for (it = entities.begin(); it != entities.end();){
			Entity *b = *it;
			b->update(time);
			if (!b->life){
				it = entities.erase(it);
				delete b;
			}
			else it++;
		}
		for (it = entities.begin(); it != entities.end(); it++){
			for (at = entities.begin(); at != entities.end(); at++) {
				if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && ((*it)->name == "easyEnemy"))) {
					(*it)->health -= 13;
					(*at)->life = false;
				}
			}
			if ((*it)->getRect().intersects(p.getRect())){
				if ((*it)->name == "easyEnemy"){
					(*it)->dx = 0;
					p.health -= 1;
				}
			}
		}
		if (!p.life)
			window.close();
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite);
		}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
