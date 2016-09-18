#pragma once
#include <SFML/Graphics.hpp>

class MyFont {
public:
    MyFont();

    const sf::Font &GetFont() const;

    void SetFont(const sf::Font &font);

private:
    sf::Font font;
};
