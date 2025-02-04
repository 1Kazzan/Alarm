#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h" 

// definir pinos GPIOs para os leds rgb e butão
#define led_green 11
#define led_blue 12
#define led_red 13
#define button 5

bool leds_active = false;
int estado = 1;

int64_t turn_off_led_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(led_red, 0);
    leds_active = false;  // Permite nova ativação pelo botão
    return 0;
}

int64_t turn_off_led_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(led_blue, 0);
    leds_active = false;  // Permite nova ativação pelo botão
    return 0;
}

int64_t turn_off_led_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(led_green, 0);
    leds_active = false;  // Permite nova ativação pelo botão
    return 0;
}

int main()
{
// permite comuniação serial e uso de printf
    stdio_init_all();

 // inicia os pinos GPIOs dos leds
    gpio_init(led_green);
    gpio_set_dir(led_green, GPIO_OUT);

    gpio_init(led_blue);
    gpio_set_dir(led_blue, GPIO_OUT);

    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT);
    
    //inicia butão

    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_up(button);
 while (true) {
    if (gpio_get(button) == 0 && !leds_active) {
        sleep_ms(50);
         if (gpio_get(button) == 0) {
            leds_active = true;
            gpio_put(led_red, 1);
            gpio_put(led_blue, 1);
             gpio_put(led_green, 1);
            add_alarm_in_ms(3000, turn_off_led_green_callback, NULL, false);
            }
        }
        sleep_ms(10);
    }
    return 0;
    }
