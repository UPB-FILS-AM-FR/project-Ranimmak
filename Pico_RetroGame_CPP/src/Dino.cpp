#include "hardware.hpp"
#include "games.hpp"

void runDino() {
    int dinoY = 44;
    int velocity = 0;
    int cactusX = 126;
    int score = 0;

    while (!pressed(PIN_B)) {
        bool onGround = dinoY >= 44;
        if ((pressed(PIN_UP) || pressed(PIN_A)) && onGround) {
            velocity = -7;
            beep(1000, 25);
        }
        velocity += 1;
        dinoY += velocity;
        if (dinoY > 44) { dinoY = 44; velocity = 0; }

        cactusX -= 3;
        if (cactusX < -8) { cactusX = 128; score++; }

        bool hit = cactusX < 28 && cactusX > 14 && dinoY > 35;
        if (hit) {
            beep(200, 120);
            cactusX = 128;
            score = 0;
        }

        clearScreen();
        display.setCursor(0, 0); display.print("Dino  "); display.print(score);
        display.drawLine(0, 61, 127, 61, SSD1306_WHITE);
        display.fillRect(20, dinoY, 12, 16, SSD1306_WHITE);
        display.drawRect(23, dinoY - 7, 8, 8, SSD1306_WHITE);
        display.fillRect(cactusX, 45, 6, 16, SSD1306_WHITE);
        updateScreen();
        delay(45);
    }
    waitRelease();
}
