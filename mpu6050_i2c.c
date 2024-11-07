#include "mpu6050_i2c.h"

static int addr = 0x68;

void mpu6050_reset() {
    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c_default, addr, buf, 2, false);
}

void mpu6050_read_raw(mpu_reading* r) {
    uint8_t buffer[6];
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c_default, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        r->accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    val = 0x43;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        r->gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    //val = 0x41;
    //i2c_write_blocking(i2c_default, addr, &val, 1, true);
    //i2c_read_blocking(i2c_default, addr, buffer, 2, false);  // False - finished with bus
    //*temp = buffer[0] << 8 | buffer[1];
}

void mpu6050_read_adjusted(mpu_reading* r) {
	mpu6050_read_raw(r);
	for(int i = 0; i < 3; i++) {
		r->gyro[i] = r->gyro[i] - r->g_offset[i];
	}
}

void mpu6050_calibrate_gyro(mpu_reading* r) {
    uint32_t gyro_cumm[3] = {0, 0, 0};
	const int N = 2000;
	for(int i = 0; i < N; i++) {
		mpu6050_read_raw(r);
		for(int j = 0; j < 3; j++) {
			gyro_cumm[j] += r->gyro[j];
		}
        sleep_ms(2);
	}
	for(int j = 0; j < 3; j++) {
		r->g_offset[j] = gyro_cumm[j] / N;
	}
}

mpu_reading* mpu6050_init() {
	mpu_reading* r = malloc(sizeof(mpu_reading));
	printf("Hello, MPU6050! Reading raw data from registers...\n");
	// This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
	i2c_init(i2c_default, 400 * 1000);
	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
	// Make the I2C pins available to picotool
	bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
	mpu6050_reset();
	mpu6050_calibrate_gyro(r);
	return r;
}
