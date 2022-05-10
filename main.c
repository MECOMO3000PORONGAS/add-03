#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int main() {
    stdio_init_all();
    
    float raux = 10000.0;
    float vcc = 3.3;
    float beta = 3977.0;
    float temp0 = 298.0;
    float r0 = 10000.0;
    
    adc_init();
    adc_gpio_init(27);
    adc_select_input(1);

    while (1) {
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        float vr2 = result * conversion_factor;
        float rntc = raux / ((vcc/vr2)-1);
        float temperaturaK = beta / (log(rntc/r0)+(beta/temp0));
        printf("resistenciavariable: %.2f KΩ\nTemperatura: %.2f °C\n", rntc/1000, temperaturaK - 273.15);
        sleep_ms(500);
    }
}