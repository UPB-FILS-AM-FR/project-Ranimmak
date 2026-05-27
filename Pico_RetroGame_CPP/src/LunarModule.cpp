#include "hardware.hpp"
#include "games.hpp"

void runLunarModule() {
    int shipX = 10;
    int shipY = 8;
    int vx = 1;
    int gravity = 0;
    int fuel = 25;

    while (!pressed(PIN_B)) {
        if ((pressed(PIN_A) || pressed(PIN_UP)) && fuel > 0) {
            gravity -= 2;
            fuel--;
            beep(1500, 15);
        }
        if (pressed(PIN_LEFT)) shipX--;
        if (pressed(PIN_RIGHT)) shipX++;

        shipX += vx;
        shipY += 1 + gravity / 8;
        gravity++;
        if (shipX < 0 || shipX > 116) vx = -vx;

        bool landed = shipY >= 54 && shipX > 96 && shipX < 116 && gravity < 9;
        bool crashed = shipY > 60 && !landed;
        if (landed || crashed) {
            clearScreen();
            drawCenteredText(landed ? "LANDED!" : "CRASH!", 24);
            updateScreen();
            beep(landed ? 1200 : 180, 200);
            delay(900);
            shipX = 10; shipY = 8; gravity = 0; fuel = 25;
        }

        clearScreen();
        display.setCursor(0, 0); display.print("Fuel:"); display.print(fuel);
        display.setCursor(82, 0); display.print("m/s:"); display.print(gravity);
        display.drawRect(shipX, shipY, 9, 8, SSD1306_WHITE);
        display.drawLine(shipX + 2, shipY + 8, shipX, shipY + 12, SSD1306_WHITE);
        display.drawLine(shipX + 7, shipY + 8, shipX + 9, shipY + 12, SSD1306_WHITE);
        if ((pressed(PIN_A) || pressed(PIN_UP)) && fuel > 0) display.drawLine(shipX + 4, shipY + 9, shipX + 4, shipY + 16, SSD1306_WHITE);
        display.fillRect(100, 62, 16, 2, SSD1306_WHITE);
        updateScreen();
        delay(70);
    }
    waitRelease();
}
