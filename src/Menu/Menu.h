#pragma once

#include "Button.h"
#include <iostream>
#include <vector>

class Menu {
public:
    Menu();

    void Draw(sf::RenderWindow & window);

private:
    const sf::Vector2f TOP_BUTTON_POSITION = {100, 100};
    const sf::Vector2f sizeOfButton = {200, 50};
    std::vector<Button> buttons;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    void DrawForeGround(sf::RenderWindow & window);
    void DrawBackGround(sf::RenderWindow & window);
};
