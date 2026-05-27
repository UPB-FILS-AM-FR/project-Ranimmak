#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.hpp"

extern Adafruit_SSD1306 display;

void initHardware();
void clearScreen();
void updateScreen();
void beep(uint16_t frequency = 900, uint16_t durationMs = 45);
bool pressed(uint8_t pin);
bool anyButtonPressed();
void waitRelease();
void drawCenteredText(const String& text, int16_t y, uint16_t color = SSD1306_WHITE);
