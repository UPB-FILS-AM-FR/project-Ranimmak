#include "hardware.hpp"
#include "games.hpp"

void runPong() {
    int ballX = 64, ballY = 32, vx = 2, vy = 1;
    int leftPaddle = 24, rightPaddle = 24;
    int scoreL = 0, scoreR = 0;

    while (!pressed(PIN_B)) {
        if (pressed(PIN_UP) && rightPaddle > 0) rightPaddle -= 2;
        if (pressed(PIN_DOWN) && rightPaddle < 48) rightPaddle += 2;
        if (ballY < leftPaddle + 4 && leftPaddle > 0) leftPaddle--;
        if (ballY > leftPaddle + 10 && leftPaddle < 48) leftPaddle++;

        ballX += vx;
        ballY += vy;
        if (ballY <= 0 || ballY >= 63) vy = -vy;
        if (ballX <= 5 && ballY >= leftPaddle && ballY <= leftPaddle + 16) vx = -vx;
        if (ballX >= 122 && ballY >= rightPaddle && ballY <= rightPaddle + 16) vx = -vx;

        if (ballX < 0) { scoreR++; ballX = 64; ballY = 32; vx = 2; }
        if (ballX > 127) { scoreL++; ballX = 64; ballY = 32; vx = -2; }

        clearScreen();
        display.setCursor(50, 0); display.print(scoreL); display.print("-"); display.print(scoreR);
        display.drawLine(64, 8, 64, 63, SSD1306_WHITE);
        display.fillRect(2, leftPaddle, 3, 16, SSD1306_WHITE);
        display.fillRect(123, rightPaddle, 3, 16, SSD1306_WHITE);
        display.fillCircle(ballX, ballY, 2, SSD1306_WHITE);
        updateScreen();
        delay(FRAME_DELAY);
    }
    waitRelease();
}
