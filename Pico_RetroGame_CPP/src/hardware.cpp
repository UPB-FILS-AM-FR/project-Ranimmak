#include "hardware.hpp"
#include <Wire.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initHardware() {
    Serial.begin(115200);

    pinMode(PIN_UP, INPUT_PULLUP);
    pinMode(PIN_DOWN, INPUT_PULLUP);
    pinMode(PIN_LEFT, INPUT_PULLUP);
    pinMode(PIN_RIGHT, INPUT_PULLUP);
    pinMode(PIN_A, INPUT_PULLUP);
    pinMode(PIN_B, INPUT_PULLUP);
    pinMode(PIN_BUZZER, OUTPUT);

    Wire.setSDA(PIN_SDA);
    Wire.setSCL(PIN_SCL);
    Wire.begin();

    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void clearScreen() {
    display.clearDisplay();
}

void updateScreen() {
    display.display();
}

void beep(uint16_t frequency, uint16_t durationMs) {
    tone(PIN_BUZZER, frequency, durationMs);
    delay(durationMs);
    noTone(PIN_BUZZER);
}

bool pressed(uint8_t pin) {
    return digitalRead(pin) == LOW;
}

bool anyButtonPressed() {
    return pressed(PIN_UP) || pressed(PIN_DOWN) || pressed(PIN_LEFT) || pressed(PIN_RIGHT) || pressed(PIN_A) || pressed(PIN_B);
}

void waitRelease() {
    while (anyButtonPressed()) delay(10);
}

void drawCenteredText(const String& text, int16_t y, uint16_t color) {
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
    display.setTextColor(color);
    display.setCursor((SCREEN_WIDTH - w) / 2, y);
    display.print(text);
}
