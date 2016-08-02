#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2f GetMousePosition(sf::RenderWindow &window);

class Button {

public:
//    Button();

//    Button(sf::Vector2f position, sf::Vector2f size, std::string str, Button::Action state);

//    Button(std::string str, Action state);

    bool IsMouseOnButton(const sf::Vector2f &mousePosition);

    bool IsMousePressed();

    void ChangeColor(sf::RenderWindow &window);

private:
    void StartGame();

    void ShowText();

    void Exit();

private:
    sf::RectangleShape rectangleShape;

    enum Action {
        START_GAME,
        SHOW_TEXT,
        EXIT
    };
    Action action;
    sf::Text text;
    sf::Vector2f size;
    sf::Vector2f upLeftCorner;
};

class Menu {

public:
    Menu();

    void Draw(sf::RenderWindow &window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Text title;

private:
    Button startGame;
    Button tutorial;
    Button aboutDesigner;
    Button exit;

};

