#include <SFML/Graphics.hpp>
#include "Classes.h"
using namespace sf;

void getPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;
 
	if (x < 685) tempX = 685;
	if (x > 1325) tempX = 1325;
	if (y < 380) tempY = 380;
	if (y > 1650) tempY = 1650;

	application.view.setCenter(tempX, tempY);
	

  //test


}
