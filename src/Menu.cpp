#include "Menu.h"

sf::Vector2f GetMousePosition(sf::RenderWindow &window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string str) {
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
        text.setCharacterSize(24);
        text.setColor(sf::Color::Yellow);
    }
    text.setFont(font);
    text.setString(str);
    text.setColor(sf::Color::White);
    text.setPosition((position.x + 20),
                     (position.y + 10));
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(rectangleShape);
    window.draw(text);
    ChangeColor(window);
}

bool Button::IsMouseOnButton(const sf::Vector2f &mousePosition) {
    return ((mousePosition.x >= mousePosition.x) && (mousePosition.x <= (upLeftCorner.x + size.x)) &&
            (mousePosition.y >= mousePosition.y) && (mousePosition.y <= (upLeftCorner.y + size.y)));
}

void Button::ChangeColor(sf::RenderWindow &window) {
    if (IsMouseOnButton(GetMousePosition(window))) {
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

}

Menu::Menu() : tutorial(position, sizeOfButton, "Tutorial"),
               startGame({position.x, position.y + 100}, sizeOfButton, "Start Game"),
               setLevel({position.x, position.y + 200}, sizeOfButton, "Set Level"),
               aboutDesigner({position.x, position.y + 300}, sizeOfButton, "About Designer"),
               exit({position.x, position.y + 400}, sizeOfButton, "Exit") {
    backgroundTexture.loadFromFile("IMG/back_3.png");
    background.setTexture(backgroundTexture);
    background.setPosition(300, 0);
}

void Menu::Draw(sf::RenderWindow &window) {
    window.draw(background);
    tutorial.draw(window);
    startGame.draw(window);
    setLevel.draw(window);
    aboutDesigner.draw(window);
    exit.draw(window);
}
