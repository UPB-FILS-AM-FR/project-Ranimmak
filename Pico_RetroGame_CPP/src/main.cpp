#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "ssd1306.hpp" 
#include <array>
#include <string>


constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;


constexpr uint UP_PIN = 2;
constexpr uint DOWN_PIN = 3;
constexpr uint LEFT_PIN = 4;
constexpr uint RIGHT_PIN = 5;
constexpr uint BUTTON1_PIN = 6;
constexpr uint BUTTON2_PIN = 7;


constexpr uint BUZZER_PIN = 18;


const std::array<const char*, 8> GAMELIST = {
    "Pong", "Snake", "Space Invaders", "Dino",
    "2048", "Tetris", "Full Speed", "Lunar Module"
};

void buzzer_beep() {
    
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, 65535);
    pwm_init(slice_num, &config, true);

   
    uint16_t level = 20000;
    pwm_set_gpio_level(BUZZER_PIN, level);

    sleep_ms(100);

    pwm_set_gpio_level(BUZZER_PIN, 0);
    pwm_deinit(slice_num);
}

int main() {
    stdio_init_all();

    
    sleep_ms(200);

    
    gpio_init(UP_PIN); gpio_set_dir(UP_PIN, GPIO_IN); gpio_pull_up(UP_PIN);
    gpio_init(DOWN_PIN); gpio_set_dir(DOWN_PIN, GPIO_IN); gpio_pull_up(DOWN_PIN);
    gpio_init(LEFT_PIN); gpio_set_dir(LEFT_PIN, GPIO_IN); gpio_pull_up(LEFT_PIN);
    gpio_init(RIGHT_PIN); gpio_set_dir(RIGHT_PIN, GPIO_IN); gpio_pull_up(RIGHT_PIN);
    gpio_init(BUTTON1_PIN); gpio_set_dir(BUTTON1_PIN, GPIO_IN); gpio_pull_up(BUTTON1_PIN);
    gpio_init(BUTTON2_PIN); gpio_set_dir(BUTTON2_PIN, GPIO_IN); gpio_pull_up(BUTTON2_PIN);

    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

  
    SSD1306 display(i2c1, SCREEN_WIDTH, SCREEN_HEIGHT); // Adjust constructor per your driver

    int current = 0;
    int game_selected = -1;

    while (true) {
        display.clear();

       
        for (size_t row = 0; row < GAMELIST.size(); row++) {
            if ((int)row == current) {
                display.fillRect(0, row * 8, SCREEN_WIDTH, 7, SSD1306::Color::White);
                display.setTextColor(SSD1306::Color::Black);
            } else {
                display.setTextColor(SSD1306::Color::White);
            }

            int text_x = SCREEN_WIDTH / 2 - (strlen(GAMELIST[row]) * 8) / 2;
            display.setCursor(text_x, row * 8);
            display.print(GAMELIST[row]);
        }

        display.display();

        sleep_ms(200);

        bool buttonPressed = false;

        while (!buttonPressed) {
            
            if ((gpio_get(DOWN_PIN) == 0 || gpio_get(RIGHT_PIN) == 0) && current < (int)GAMELIST.size() - 1) {
                current++;
                buttonPressed = true;
            }
            else if ((gpio_get(UP_PIN) == 0 || gpio_get(LEFT_PIN) == 0) && current > 0) {
                current--;
                buttonPressed = true;
            }
            else if (gpio_get(BUTTON1_PIN) == 0 || gpio_get(BUTTON2_PIN) == 0) {
                buttonPressed = true;
                game_selected = current;
            }
            sleep_ms(10);
        }

        
        buzzer_beep();

        if (game_selected >= 0) {
            display.clear();
            display.display();

            
            switch (game_selected) {
                case 0:
                    
                    break;
                case 1:
                    
                    break;
                case 2:
                    
                    break;
                case 3:
                    
                    break;
                case 4:
                    
                    break;
                case 5:
                    
                    break;
                case 6:
                    
                    break;
                case 7:
                    
                    break;
            }

            game_selected = -1;
        }
    }
    return 0;
}