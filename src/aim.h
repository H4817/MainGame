#include <SFML/Graphics.hpp>

using namespace sf;

struct Aim {
public:
    Vector2f position;
    Texture texture1;
    Sprite aim;
    Aim();
    void Draw(RenderWindow & window);
};