#include "Menu.h"

sf::Vector2f GetMousePosition(sf::RenderWindow &window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string str, int state) {
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
    action = static_cast<Action>(state);
}

void Button::ProcessState() {
    if (action == 0) {
        StartGame();
    }
    else if (action == 1) {
        ShowText();
    }
    else {
        Exit();
    }
}

void Button::draw(sf::RenderWindow &window) {
    Update(window);
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

void Button::Update(sf::RenderWindow &window) {
    if (IsMouseOnButton(GetMousePosition(window))) {
        if (IsMousePressed()) {
            ProcessState();
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

}

void Button::StartGame() {

}

void Button::Exit() {
    exit(0);
}

Menu::Menu() : tutorial(position, sizeOfButton, "Tutorial", 1),
               startGame({position.x, position.y + 100}, sizeOfButton, "Start Game", 1),
               setLevel({position.x, position.y + 200}, sizeOfButton, "Set Level", 1),
               aboutDesigner({position.x, position.y + 300}, sizeOfButton, "About Designer", 1),
               exit({position.x, position.y + 400}, sizeOfButton, "Exit", 2) {
    backgroundTexture.loadFromFile("IMG/back_3.png");
    background.setTexture(backgroundTexture);
    if (!font.loadFromFile("Assets/hemi-head.ttf"))
        printf("fonts are not found\n");
    else {
        text.setFont(font);
        text.setString("test");
        text.setCharacterSize(24);
        text.setColor(sf::Color::White);
    }
}

void Menu::Draw(sf::RenderWindow &window) {
    window.draw(background);
    if (m_state == SHOW_BUTTONS) {
        tutorial.draw(window);
        startGame.draw(window);
        setLevel.draw(window);
        aboutDesigner.draw(window);
        exit.draw(window);
    }
    else {
        window.draw(text);
    }
}
