#include "shared/fan_api.h"

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <fcntl.h>
#include <stdlib.h>

int begin()
{
	int fd = 0;
	char *fileName = I2C_PATH;

	// Open port for reading and writing
	if ((fd = open(fileName, O_RDWR)) < 0)
	{
		exit(1);
	}

	// Set the port options and set the address of the device
	if (ioctl(fd, I2C_SLAVE, COOLER_I2C_ADDRESS) < 0)
	{
		close(fd);
		exit(1);
	}
	return fd;
}

void i2cWriteByteData(int fd, __u8 address, __u8 value)
{
	if (0 > i2c_smbus_write_byte_data(fd, address, value))
	{
		close(fd);
		exit(1);
	}
}

int setSpeed(unsigned char value)
{
	int fd = begin();
	i2cWriteByteData(fd, COOLER_COMMAND, value);
	close(fd);
	return fd;
}

static double getCpuTemp(void)
{
	int fd;
	double temp = 0;
	char buf[MAX_SIZE];

	// open /sys/class/thermal/thermal_zone0/temp
	fd = open(TEMP_PATH, O_RDONLY);
	if (fd < 0)
	{
		return -1;
	}

	// read value
	if (read(fd, buf, MAX_SIZE) < 0)
	{
		return -1;
	}

	temp = atoi(buf) / 1000.0;
	close(fd);
	return temp;
}

void calibration()
{
	int fd = begin();
	setSpeed(0x0A);
	double temp;
	while (1)
	{
		temp = getCpuTemp();
		if (temp > 40)
		{
			setSpeed(LEVEL_2);
		}
		else if (temp > 50)
		{
			setSpeed(LEVEL_3);
		}
		else if (temp > 55)
		{
			setSpeed(LEVEL_4);
		}
		else if (temp > 60)
		{
			setSpeed(LEVEL_5);
		}
		else if (temp > 65)
		{
			setSpeed(LEVEL_6);
		}
		else
		{
			setSpeed(LEVEL_1);
		}
		// printf("temp: %f\n",temp);
		usleep(1000);
	}
	close(fd);
}