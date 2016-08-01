#pragma once

#include <SFML/Graphics.hpp>


class Button {
public:
    Button();

    Button(sf::Vector2f size, sf::Vector2f position, std::string str, Action state);

    Button(std::string str, Action state);

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
    std::string m_string;
    Vector2f size;
    sf::Vector2f position;
};

class Menu {
public:
    Menu();

    void Draw();

private:
    sf::sprite background;
    std::string title;

private:
    Button startGame;
    Button tutorial;
    Button aboutDesigner;
    Button exit;

};

