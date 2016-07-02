#pragma once
#include <SFML/Graphics.hpp>

class Shield {
public:
    Shield();
    void Draw(sf::RenderWindow & window, sf::Vector2f position);
private:
    const sf::Vector2i OFFSET = {35, 25};
    sf::Texture texture1;
    sf::Sprite shield;
};