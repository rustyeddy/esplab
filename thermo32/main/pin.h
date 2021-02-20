#pragma once

typedef struct {
    gpio_num_t pin;			// digital gpio pin
    gpio_mode_t mode;			// input or output
} pin_t;

static pin_t* get_pin(gpio_num_t pin, gpio_mode_t mode) {
    pin_t *p = calloc(1, sizeof(pin_t));
    assert(p);

    p->pin = pin;
    p->mode = mode;
    gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, mode);

    return p;
}

static void on(pin_t *p) { gpio_set_level(p->pin, 1); }
static void off(pin_t *p) { gpio_set_level(p->pin, 0); }
//static void toggle(pin_t *p) { gpio_get_level(p->pin) ? off(p) : on(p); }
