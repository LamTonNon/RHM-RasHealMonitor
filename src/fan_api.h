#ifndef FAN_API_H
#define FAN_API_H

#define COOLER_I2C_ADDRESS 0x0D
#define COOLER_COMMAND 0x08

#define LEVEL_1 0x00
#define LEVEL_2 0x02
#define LEVEL_3 0x04
#define LEVEL_4 0x06
#define LEVEL_5 0x08
#define LEVEL_6 0x09
#define LEVEL_7 0x01



void initCooler();

int setSpeed(unsigned char value);

#endif