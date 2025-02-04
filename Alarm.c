#include <stdio.h>
#include "pico/stdlib.h" // biblioteca padrão para trabalhar com a raspberry pi pico
#include "pico/time.h" // Biblioteca para gerenciamento de temporizadores e alarmes.

// definir pinos GPIOs para os leds rgb e butão
#define led_green 11
#define led_blue 12
#define led_red 13
#define button 5

bool leds_active = false; // indica que os leds estão acessos

// função de callback para desligar o led vermelho após o tempo programado.
int64_t turn_off_led_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(led_red, 0);
    return 0;
}

// função de callback para desligar o led azul após o tempo programado.
int64_t turn_off_led_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(led_blue, 0);
    return 0;
}

// função de callback para desligar o led verde após o tempo programado.
int64_t turn_off_led_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(led_green, 0);
    leds_active = false;  // Permite nova ativação pelo botão
    return 0;
}

int main()
{
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
    // verifica se o botão foi pressionado e se os leds ainda não estão ativos
    if (gpio_get(button) == 0 && !leds_active) {
        sleep_ms(50); // debounce

        // ativa os leds se o botão estiver pressionado
         if (gpio_get(button) == 0) {
            leds_active = true;

            //liga os leds
            gpio_put(led_red, 1);
            gpio_put(led_blue, 1);
            gpio_put(led_green, 1);

            // Configura alarmes para desligar os LEDs após os tempos definidos
            add_alarm_in_ms(3000, turn_off_led_red_callback, NULL, false);
            add_alarm_in_ms(6000, turn_off_led_blue_callback, NULL, false);
            add_alarm_in_ms(9000, turn_off_led_green_callback, NULL, false);
            }
        }
        // Pausa de 10 segundos para reduzir o uso da CPU.
        sleep_ms(10000);
    }
    return 0;
    }
