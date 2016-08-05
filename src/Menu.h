#pragma once

#include <SFML/Graphics.hpp>

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

    void draw(sf::RenderWindow &window);

    bool IsMouseOnButton(const sf::Vector2f &mousePosition);

    bool IsMousePressed();

    void Update(sf::RenderWindow &window);

    sf::Vector2f GetPosition();

    sf::Vector2f GetSize();
    Action GetAction();

private:
    sf::RectangleShape rectangleShape;
    Action action;
    sf::Font font;
    sf::Text text;
    sf::Vector2f size;
    sf::Vector2f upLeftCorner;
};

class Menu {

public:
    Menu();

    void Draw(sf::RenderWindow &window);

    void DrawButtons(sf::RenderWindow &window);

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
    Button exit;

};

