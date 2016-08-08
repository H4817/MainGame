#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

sf::Vector2f GetMousePosition(sf::RenderWindow &window);

enum Action {
    SHOW_BUTTONS,
    START_GAME,
    SHOW_TEXT,
    EXIT
};

class Button {

public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string str, Action state);

    void draw(sf::RenderWindow &window, GameState &gameState);

    bool IsMouseOnButton(const sf::Vector2f &mousePosition);

    bool IsMousePressed();

    void Update(sf::RenderWindow &window, GameState &gameState);

    void ProcessState(GameState &gameState);

    sf::Vector2f GetPosition();

    sf::Vector2f GetSize();

    Action GetAction();

private:
    void StartGame();

    void ShowText();

    void Exit();

private:
    sf::RectangleShape rectangleShape;
    Action action;
    sf::Font font;
    sf::Text text;
    sf::Text additionalText;
    sf::Vector2f size;
    sf::Vector2f upLeftCorner;
};

class Menu {

public:
    Menu();

    void Draw(sf::RenderWindow &window, GameState &gameState);

    void DrawButtons(sf::RenderWindow &window, GameState &gameState);

    void ProcessState();

private:
    void StartGame();

    void ShowText();

    void Exit();

private:
    sf::Texture backgroundTexture;
    sf::Font font;
    sf::Text text;
    sf::Sprite background;

    Action m_state;
    const sf::Vector2f sizeOfButton = {200, 50};
    const sf::Vector2f position = {100, 100};
    Button setLevel;
    Button startGame;
    Button tutorial;
    Button aboutDesigner;
    Button m_exit;

};

