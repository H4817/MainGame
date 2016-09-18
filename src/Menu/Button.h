#pragma once

#include <SFML/Graphics.hpp>
#include "MyFont.h"

enum Action {
    SHOW_BUTTONS,
    START_GAME,
    SHOW_TEXT,
    EXIT
};

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string str, Action state);

    Action GetState();

    void SetState(Action newState);

    bool IsMouseOnButton(sf::RenderWindow &window);

    bool IsMousePressed(sf::RenderWindow &window);

    void ProcessEvents(sf::RenderWindow &window);

    void Draw(sf::RenderWindow &window);

private:
    void ProcessState();

    void SetSelectedColor();

    void SetNotSelectedColor();

private:
    sf::RectangleShape rectangleShape;
    Action state;
    MyFont myFont;
    sf::Text text;
//    sf::Text additionalText;
    sf::Vector2f size;
    sf::Vector2f upLeftCorner;
};
