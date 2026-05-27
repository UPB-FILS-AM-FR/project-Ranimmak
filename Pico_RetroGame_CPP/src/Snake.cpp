#include "hardware.hpp"
#include "games.hpp"

struct Point { int x; int y; };

void runSnake() {
    Point snake[64];
    int length = 5;
    int dx = 1, dy = 0;
    Point food{80, 32};
    for (int i = 0; i < length; ++i) snake[i] = {40 - i * 4, 32};

    while (!pressed(PIN_B)) {
        if (pressed(PIN_UP) && dy == 0) { dx = 0; dy = -1; }
        if (pressed(PIN_DOWN) && dy == 0) { dx = 0; dy = 1; }
        if (pressed(PIN_LEFT) && dx == 0) { dx = -1; dy = 0; }
        if (pressed(PIN_RIGHT) && dx == 0) { dx = 1; dy = 0; }

        for (int i = length - 1; i > 0; --i) snake[i] = snake[i - 1];
        snake[0].x += dx * 4;
        snake[0].y += dy * 4;

        if (snake[0].x < 0) snake[0].x = 124;
        if (snake[0].x > 124) snake[0].x = 0;
        if (snake[0].y < 0) snake[0].y = 60;
        if (snake[0].y > 60) snake[0].y = 0;

        if (abs(snake[0].x - food.x) < 4 && abs(snake[0].y - food.y) < 4) {
            if (length < 64) length++;
            food.x = (random(0, 31) * 4);
            food.y = (random(0, 15) * 4);
            beep(1300, 35);
        }

        clearScreen();
        display.fillRect(food.x, food.y, 4, 4, SSD1306_WHITE);
        for (int i = 0; i < length; ++i) display.fillRect(snake[i].x, snake[i].y, 4, 4, SSD1306_WHITE);
        updateScreen();
        delay(90);
    }
    waitRelease();
}
