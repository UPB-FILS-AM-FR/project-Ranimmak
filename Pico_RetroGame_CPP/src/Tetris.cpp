#include "hardware.hpp"
#include "games.hpp"

void runTetris() {
    int blockX = 5;
    int blockY = 0;
    int score = 0;
    bool grid[10][16] = {};

    while (!pressed(PIN_B)) {
        if (pressed(PIN_LEFT) && blockX > 0) blockX--;
        if (pressed(PIN_RIGHT) && blockX < 8) blockX++;
        if (pressed(PIN_DOWN)) blockY++;

        blockY++;
        if (blockY >= 15) {
            grid[blockX][15] = true;
            grid[blockX + 1][15] = true;
            blockX = random(0, 8);
            blockY = 0;
            score += 10;
            beep(700, 25);
        }

        clearScreen();
        display.setCursor(72, 0); display.print("Tetris");
        display.setCursor(72, 10); display.print("Scr:"); display.print(score);
        display.drawRect(0, 0, 62, 64, SSD1306_WHITE);
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 16; ++y) {
                if (grid[x][y]) display.fillRect(2 + x * 6, y * 4, 5, 4, SSD1306_WHITE);
            }
        }
        display.fillRect(2 + blockX * 6, blockY * 4, 11, 8, SSD1306_WHITE);
        updateScreen();
        delay(110);
    }
    waitRelease();
}
