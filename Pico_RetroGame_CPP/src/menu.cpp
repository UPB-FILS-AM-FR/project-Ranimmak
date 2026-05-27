#include "menu.hpp"
#include "hardware.hpp"

static const char* GAME_NAMES[GAME_COUNT] = {
    "Pong",
    "Snake",
    "Space Invaders",
    "Dino",
    "2048",
    "Tetris",
    "Full Speed",
    "Lunar Module"
};

GameId showMainMenu() {
    int selected = 0;
    waitRelease();

    while (true) {
        clearScreen();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(16, 0);
        display.print("PICO RETRO GAME");
        display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

        for (int i = 0; i < GAME_COUNT; ++i) {
            int y = 14 + i * 6;
            if (i == selected) {
                display.fillRect(0, y - 1, 128, 7, SSD1306_WHITE);
                display.setTextColor(SSD1306_BLACK);
                display.setCursor(4, y);
                display.print("> ");
                display.print(GAME_NAMES[i]);
                display.setTextColor(SSD1306_WHITE);
            } else {
                display.setCursor(10, y);
                display.print(GAME_NAMES[i]);
            }
        }
        updateScreen();

        if (pressed(PIN_DOWN) || pressed(PIN_RIGHT)) {
            selected = (selected + 1) % GAME_COUNT;
            beep();
            waitRelease();
        }
        if (pressed(PIN_UP) || pressed(PIN_LEFT)) {
            selected = (selected + GAME_COUNT - 1) % GAME_COUNT;
            beep();
            waitRelease();
        }
        if (pressed(PIN_A) || pressed(PIN_B)) {
            beep(1200, 70);
            waitRelease();
            return static_cast<GameId>(selected);
        }
        delay(20);
    }
}
