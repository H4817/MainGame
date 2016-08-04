#pragma once

#include <SFML/Graphics.hpp>

sf::Vector2f GetMousePosition(sf::RenderWindow &window);

class Button {

public:
    Button(sf::Vector2f position, sf::Vector2f size, std::string str, int state);

    void draw(sf::RenderWindow &window);

    bool IsMouseOnButton(const sf::Vector2f &mousePosition);

    bool IsMousePressed();

    void Update(sf::RenderWindow &window);

    void ProcessState();

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
    sf::Font font;
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
    sf::Font font;
    sf::Text text;
    sf::Sprite background;

private:
    enum State {
        SHOW_TEXT,
        SHOW_BUTTONS
    };
    State m_state;
    const sf::Vector2f sizeOfButton = {200, 50};
    const sf::Vector2f position = {100, 100};
    Button setLevel;
    Button startGame;
    Button tutorial;
    Button aboutDesigner;
    Button exit;

};

