#include "hardware.hpp"
#include "games.hpp"

void runInvaders() {
    int playerX = 58;
    int laserX = -1, laserY = -1;
    int alienOffset = 0, alienDir = 1;
    bool aliens[3][5];
    for (auto &row : aliens) for (bool &a : row) a = true;

    while (!pressed(PIN_B)) {
        if (pressed(PIN_LEFT) && playerX > 0) playerX -= 2;
        if (pressed(PIN_RIGHT) && playerX < 116) playerX += 2;
        if (pressed(PIN_A) && laserY < 0) { laserX = playerX + 5; laserY = 54; beep(1400, 20); }
        if (laserY >= 0) laserY -= 4;
        if (laserY < 0) laserY = -1;

        alienOffset += alienDir;
        if (alienOffset > 10 || alienOffset < -10) alienDir = -alienDir;

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 5; ++c) {
                int ax = 15 + c * 20 + alienOffset;
                int ay = 12 + r * 10;
                if (aliens[r][c] && laserY >= ay && laserY <= ay + 8 && laserX >= ax && laserX <= ax + 10) {
                    aliens[r][c] = false;
                    laserY = -1;
                    beep(600, 30);
                }
            }
        }

        clearScreen();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 5; ++c) {
                if (aliens[r][c]) {
                    int ax = 15 + c * 20 + alienOffset;
                    int ay = 12 + r * 10;
                    display.drawRect(ax, ay, 10, 7, SSD1306_WHITE);
                    display.drawPixel(ax + 2, ay + 2, SSD1306_WHITE);
                    display.drawPixel(ax + 7, ay + 2, SSD1306_WHITE);
                }
            }
        }
        display.fillTriangle(playerX, 62, playerX + 6, 52, playerX + 12, 62, SSD1306_WHITE);
        if (laserY >= 0) display.drawLine(laserX, laserY, laserX, laserY + 5, SSD1306_WHITE);
        updateScreen();
        delay(FRAME_DELAY);
    }
    waitRelease();
}
