#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

/* 
   GPIO PICO_DEFAULT_I2C_SDA_PIN (On Pico this is GP4 (pin 6)) -> SDA on MPU6050 board
   GPIO PICO_DEFAULT_I2C_SCL_PIN (On Pico this is GP5 (pin 7)) -> SCL on MPU6050 board
   3.3v (pin 36) -> VCC on MPU6050 board
   GND (pin 38)  -> GND on MPU6050 board
*/

// By default these devices  are on bus address 0x68

struct mpu_reading {
	int16_t accel[3];
	int16_t gyro[3];
	int16_t g_offset[3];
} typedef mpu_reading;

void mpu6050_reset();

void mpu6050_read_raw(mpu_reading* r);

void mpu6050_read_adjusted(mpu_reading* r);
void mpu6050_calibrate_gyro(mpu_reading* r);
mpu_reading* mpu6050_init();
