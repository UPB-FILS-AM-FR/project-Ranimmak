#include "hardware.hpp"
#include "games.hpp"

void runFullSpeed() {
    int motoX = 0;
    int rivalY = -20;
    int rivalX = 0;
    int score = 0;

    while (!pressed(PIN_B)) {
        if (pressed(PIN_LEFT) && motoX > -25) motoX -= 3;
        if (pressed(PIN_RIGHT) && motoX < 25) motoX += 3;
        rivalY += 3;
        if (rivalY > 64) {
            rivalY = -10;
            rivalX = random(-25, 25);
            score++;
        }

        if (rivalY > 48 && abs(rivalX - motoX) < 8) {
            beep(180, 130);
            rivalY = -10;
            score = 0;
        }

        clearScreen();
        display.setCursor(0, 0); display.print("Full Speed "); display.print(score * 5); display.print("km/h");
        display.drawLine(50, 22, 10, 63, SSD1306_WHITE);
        display.drawLine(78, 22, 118, 63, SSD1306_WHITE);
        display.drawLine(60, 22, 45, 63, SSD1306_WHITE);
        display.drawLine(68, 22, 83, 63, SSD1306_WHITE);
        display.fillRect(62 + motoX, 54, 5, 9, SSD1306_WHITE);
        display.fillRect(62 + rivalX, rivalY, 5, 9, SSD1306_WHITE);
        updateScreen();
        delay(45);
    }
    waitRelease();
}
