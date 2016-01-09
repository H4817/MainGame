#include "Bar.h"

LifeBar::LifeBar() {
    image.loadFromFile("IMG/RedBar4.png");
    t.loadFromImage(image);
    s.setTexture(t);

    entitiesBar.loadFromFile("IMG/Enemy.png");
    entitiesTexture.loadFromImage(entitiesBar);
    bar2.setTexture(entitiesTexture);
    bar.setRotation(180);
    bar.setFillColor(Color(0, 0, 0));

}

void LifeBar::updateEnemy(int Shields, int Health) {
    barOffset = {(maxHealth - Health)*201.5/maxHealth, 10};
    if ((Health > 0) && (Health < maxHealth)) {
        bar.setSize(barOffset);
    }
}

void LifeBar::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    s.setPosition((center.x - size.x  / halfScreen) + 500, center.y - size.y / halfScreen);
    bar.setPosition((center.x - size.x  / halfScreen) + 950, (center.y - size.y / halfScreen) + 1035);
    bar2.setPosition((center.x - size.x  / halfScreen) + 750, (center.y - size.y / halfScreen) + 1020);

    window.draw(s);
    window.draw(bar2);
    window.draw(bar);
}
