#include "mpu6050_i2c.h"
#include "drv8833.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
	stdio_init_all();
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/mpu6050_i2c example requires a board with I2C pins
    puts("Default I2C pins were not defined");
    return 0;
#else
    //mpu_reading* r = mpu6050_init();
    //while (1) {
	    //mpu6050_read_adjusted(r);
        // These are the raw numbers from the chip, so will need tweaking to be really useful.
        // See the datasheet for more information
        //printf("Acc. X = %d, Y = %d, Z = %d\n", r->accel[0], r->accel[1], r->accel[2]);
        //printf("Gyro. X = %d, Y = %d, Z = %d\n", r->gyro[0], r->gyro[1], r->gyro[2]);
        //printf("Temp. = %f\n", (temp / 340.0) + 36.53);
        //sleep_ms(100);
    //}
    drv* d = drv_init(18, 10000);
    drv_set_speed(50, d);
#endif
}
