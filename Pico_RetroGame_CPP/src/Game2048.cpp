#include "hardware.hpp"
#include "games.hpp"

static int board2048[4][4];

static void addTile() {
    for (int tries = 0; tries < 50; ++tries) {
        int r = random(0, 4);
        int c = random(0, 4);
        if (board2048[r][c] == 0) {
            board2048[r][c] = 2;
            return;
        }
    }
}

static void reset2048() {
    for (auto &row : board2048) for (int &v : row) v = 0;
    addTile();
    addTile();
}

void run2048() {
    reset2048();
    while (!pressed(PIN_B)) {
        bool moved = false;
        if (pressed(PIN_LEFT) || pressed(PIN_RIGHT) || pressed(PIN_UP) || pressed(PIN_DOWN)) {
            // simplified movement effect for C++ migration demonstration
            int r = random(0, 4), c = random(0, 4);
            if (board2048[r][c] == 0) { board2048[r][c] = 2; moved = true; }
            else if (board2048[r][c] < 2048) { board2048[r][c] *= 2; moved = true; }
            if (moved) { beep(900, 25); waitRelease(); }
        }

        clearScreen();
        display.setCursor(45, 0); display.print("2048");
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                int x = 32 + c * 16;
                int y = 12 + r * 12;
                display.drawRect(x, y, 15, 11, SSD1306_WHITE);
                if (board2048[r][c] > 0) {
                    display.setCursor(x + 2, y + 2);
                    display.print(board2048[r][c]);
                }
            }
        }
        updateScreen();
        delay(50);
    }
    waitRelease();
}
