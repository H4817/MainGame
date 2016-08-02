#include "Menu.h"

sf::Vector2f GetMousePosition(sf::RenderWindow &window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
        rectangleShape.setOutlineColor(sf::Color::Black);
        text.setColor(sf::Color::White);
    }
}

void Button::ShowText() {

}

void Button::StartGame() {

}

void Button::Exit() {

}

Menu::Menu()  /*:aboutDesigner({800, 400}, {400, 200}, "text", Button::SHOW_TEXT),
               startGame({800, 600}, {400, 200}, "Start Game", Button::START_GAME),
               tutorial({800, 800}, {400, 200}, "Tutorial", Button::SHOW_TEXT),
               exit({800, 1000}, {400, 200}, "Exit", Button::EXIT) */{
    backgroundTexture.loadFromFile("IMG/back_3.png");
    background.setTexture(backgroundTexture);
}

void Menu::Draw(sf::RenderWindow &window) {
    window.draw(background);
}
