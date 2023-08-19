#ifndef FAN_API_H
#define FAN_API_H

#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define COOLER_I2C_ADDRESS 0x0D
#define COOLER_COMMAND 0x08
#define I2C_PATH "/dev/i2c-1"
#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 32

#define LEVEL_1 0x00
#define LEVEL_2 0x02
#define LEVEL_3 0x04
#define LEVEL_4 0x06
#define LEVEL_5 0x08
#define LEVEL_6 0x09
#define LEVEL_7 0x0A



void initCooler();

int setSpeed(unsigned char value);

void i2cWriteByteData(int fd, __u8 address, __u8 value);

#endif