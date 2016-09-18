#include <stdlib.h>
#include "Button.h"

void Button::SetSelectedColor() {
    rectangleShape.setOutlineColor(sf::Color::Yellow);
    text.setOutlineColor(sf::Color::Yellow);
}

void Button::SetNotSelectedColor() {
    rectangleShape.setOutlineColor(sf::Color::White);
    text.setOutlineColor(sf::Color::White);
}

void Button::Draw(sf::RenderWindow &window) {
    window.draw(rectangleShape);
    window.draw(text);
}

bool Button::IsMouseOnButton(sf::RenderWindow &window) {
    auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return ((mousePosition.x >= upLeftCorner.x) && (mousePosition.x <= (upLeftCorner.x + size.x)) &&
            (mousePosition.y >= upLeftCorner.y) && (mousePosition.y <= (upLeftCorner.y + size.y)));
}

bool Button::IsMousePressed(sf::RenderWindow &window) {
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::ProcessState() {
    switch (state) {
        case START_GAME:
            break;
        case SHOW_TEXT:
            break;
        case EXIT:
            exit(0);
        default:
            break;
    }
}

void Button::ProcessEvents(sf::RenderWindow &window) {
    if (IsMouseOnButton(window)) {
        if (IsMousePressed(window)) {
            ProcessState();
        }
        SetSelectedColor();
    }
    else {
        SetNotSelectedColor();
    }
    Draw(window);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string str, Action state) {
    upLeftCorner = position;
    Button::size = size;
    rectangleShape.setSize(size);
    rectangleShape.setPosition(upLeftCorner);
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setFillColor(sf::Color::Black);
    SetNotSelectedColor();
    text.setFont(myFont.GetFont());
    text.setString(str);
    text.setCharacterSize(24);
    text.setPosition((position.x + 20),
                     (position.y + 10));
    SetState(state);
}

Action Button::GetState() {
    return state;
}

void Button::SetState(Action newState) {
    state = newState;
}
