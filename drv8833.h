struct drv {
    int16_t max_cycles;
    int16_t high_cycles;
    int16_t pin;
    uint16_t slice_num;
} typedef drv;

drv* drv_init(int16_t pin, int16_t max_cycles);

void drv_set_speed(int16_t speed, drv* drv);
