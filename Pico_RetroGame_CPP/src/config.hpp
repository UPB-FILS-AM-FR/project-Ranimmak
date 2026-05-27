#pragma once
#include <Arduino.h>

constexpr uint8_t SCREEN_WIDTH  = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr uint8_t OLED_ADDR     = 0x3C;

// Raspberry Pi Pico pins used by the original MicroPython prototype
constexpr uint8_t PIN_UP      = 2;
constexpr uint8_t PIN_DOWN    = 3;
constexpr uint8_t PIN_LEFT    = 4;
constexpr uint8_t PIN_RIGHT   = 5;
constexpr uint8_t PIN_A       = 6;
constexpr uint8_t PIN_B       = 7;
constexpr uint8_t PIN_SDA     = 14;
constexpr uint8_t PIN_SCL     = 15;
constexpr uint8_t PIN_BUZZER  = 18;

constexpr uint16_t FRAME_DELAY = 35;
