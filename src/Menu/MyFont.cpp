#include "MyFont.h"

MyFont::MyFont() {
    if (!font.loadFromFile("src/Menu/hemi-head.ttf"))
        printf("fonts are not found\n");
}

const sf::Font &MyFont::GetFont() const {
    return font;
}

void MyFont::SetFont(const sf::Font &font) {
    MyFont::font = font;
}
