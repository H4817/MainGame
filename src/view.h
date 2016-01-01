#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;
void getPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;
 
	if (x < 685) tempX = 685;
	if (x > 1325) tempX = 1325;
	if (y < 380) tempY = 380;
	if (y > 1650) tempY = 1650;
 
	view.setCenter(tempX, tempY);
	
}