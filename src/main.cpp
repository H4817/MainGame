#include "Application.h"

int main() {
    RenderWindow window;
    Menu menu;
    for (size_t i = 1; i < 5; ++i) {
        StartGame(i, window, menu);
    }
    return 0;
}
