#include "Menu.h"
#include "Button.h"

Menu::Menu() {
    buttons = {{TOP_BUTTON_POSITION,                                  sizeOfButton, "Tutorial",   SHOW_TEXT},
               {{TOP_BUTTON_POSITION.x, TOP_BUTTON_POSITION.y + 100}, sizeOfButton, "Start Game", START_GAME}};
    backgroundTexture.loadFromFile("IMG/back_3.png");
    background.setTexture(backgroundTexture);

}

void Menu::Draw(sf::RenderWindow &window) {
    window.clear();
    DrawBackGround(window);
    DrawForeGround(window);
    window.display();
}

void Menu::DrawBackGround(sf::RenderWindow &window) {
    window.draw(background);
}

void Menu::DrawForeGround(sf::RenderWindow &window) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].ProcessEvents(window);
    }
}
