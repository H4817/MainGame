#include "Menu.h"

sf::Vector2f GetMousePosition(sf::RenderWindow &window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string str, Action state) {
    upLeftCorner = position;
    Button::size = size;
    rectangleShape.setSize(size);
    rectangleShape.setPosition(upLeftCorner);
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setFillColor(sf::Color::Black);
    rectangleShape.setOutlineColor(sf::Color::White);
    if (!font.loadFromFile("Assets/hemi-head.ttf"))
        printf("fonts are not found\n");
    else {
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(24);
        text.setColor(sf::Color::White);
        text.setPosition((position.x + 20),
                         (position.y + 10));
    }
    action = state;
}

void Button::ProcessState(GameState &gameState) {
    if (action == START_GAME) {
        gameState = GAME;
    }
    else if (action == SHOW_TEXT) {
        ShowText();
    }
    else if (action == EXIT) {
        Exit();
    }
}

sf::Vector2f Button::GetPosition() {
    return upLeftCorner;
}

sf::Vector2f Button::GetSize() {
    return size;
}

Action Button::GetAction() {
    return action;
}

void Button::draw(sf::RenderWindow &window, GameState &gameState) {
    Update(window, gameState);
    window.draw(rectangleShape);
    window.draw(text);
}

bool Button::IsMousePressed() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool Button::IsMouseOnButton(const sf::Vector2f &mousePosition) {
    return ((mousePosition.x >= upLeftCorner.x) && (mousePosition.x <= (upLeftCorner.x + size.x)) &&
            (mousePosition.y >= upLeftCorner.y) && (mousePosition.y <= (upLeftCorner.y + size.y)));
}

void Button::Update(sf::RenderWindow &window, GameState &gameState) {
    if (IsMouseOnButton(GetMousePosition(window))) {
        if (IsMousePressed()) {
            ProcessState(gameState);
        }
        rectangleShape.setOutlineColor(sf::Color::Yellow);
        text.setColor(sf::Color::Yellow);
    }
    else {
        rectangleShape.setOutlineColor(sf::Color::White);
        text.setColor(sf::Color::White);
    }
}

void Button::ShowText() {
//    printf("ShowText");
}

void Button::StartGame() {
//    printf("StartGame");
}

void Button::Exit() {
    printf("Exit");
    exit(0);
}

Menu::Menu() : tutorial(position, sizeOfButton, "Tutorial", SHOW_TEXT),
               startGame({position.x, position.y + 100}, sizeOfButton, "Start Game", START_GAME),
               setLevel({position.x, position.y + 200}, sizeOfButton, "Set Level", SHOW_TEXT),
               aboutDesigner({position.x, position.y + 300}, sizeOfButton, "About Designer", SHOW_TEXT),
               m_exit({position.x, position.y + 400}, sizeOfButton, "Exit", EXIT) {
    backgroundTexture.loadFromFile("IMG/back_3.png");
    background.setTexture(backgroundTexture);
    m_state = SHOW_BUTTONS;
    if (!font.loadFromFile("Assets/hemi-head.ttf"))
        printf("fonts are not found\n");
    else {
        text.setFont(font);
        text.setString("test");
        text.setCharacterSize(24);
        text.setColor(sf::Color::White);
    }
}

void Menu::DrawButtons(sf::RenderWindow &window, GameState &gameState) {
    tutorial.draw(window, gameState);
    startGame.draw(window, gameState);
    setLevel.draw(window, gameState);
    aboutDesigner.draw(window, gameState);
    m_exit.draw(window, gameState);
}

void Menu::Draw(sf::RenderWindow &window, GameState &gameState) {
    window.draw(background);
    if (m_state == SHOW_BUTTONS) {
        DrawButtons(window, gameState);
    }
    else {
        window.draw(text);
    }
}
