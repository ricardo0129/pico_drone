#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "drv8833.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

drv* drv_init(int16_t pin, int16_t max_cycles) {
    printf("Initializing pin %d with PWM, max cycles: %d\n", pin, max_cycles);
    drv* d = (drv*)malloc(sizeof(drv));
    d->pin = pin;
    d->max_cycles = max_cycles;

    gpio_set_function(pin, GPIO_FUNC_PWM);
    d->slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(d->slice_num, d->max_cycles);
    pwm_set_enabled(d->slice_num, true);
    return d;
}

void drv_set_speed(int16_t speed, drv* d) {
    printf("Setting speed %d on pin %d\n", speed, d -> pin);
    d->high_cycles = speed * d->max_cycles / 100;
    pwm_set_chan_level(d->slice_num, PWM_CHAN_A, d->high_cycles);
}
