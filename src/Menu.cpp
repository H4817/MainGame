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

void Menu::ProcessState() {
    if (m_state == START_GAME) {
        StartGame();
    }
    else if (m_state == SHOW_TEXT) {
        ShowText();
    }
    else if (m_state == EXIT){
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
//            ProcessState();
            GetAction();
        }
        rectangleShape.setOutlineColor(sf::Color::Yellow);
        text.setColor(sf::Color::Yellow);
    }
    else {
        rectangleShape.setOutlineColor(sf::Color::White);
        text.setColor(sf::Color::White);
    }
}

void Menu::ShowText() {

}

void Menu::StartGame() {

}

void Menu::Exit() {
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

void Menu::DrawButtons(sf::RenderWindow &window) {
    tutorial.draw(window);
    startGame.draw(window);
    setLevel.draw(window);
    aboutDesigner.draw(window);
    m_exit.draw(window);

}

void Menu::Draw(sf::RenderWindow &window) {
    window.draw(background);
    if (m_state == SHOW_BUTTONS) {
        DrawButtons(window);
    }
    else {
        window.draw(text);
    }
}
