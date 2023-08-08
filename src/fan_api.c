#include "fan_api.h"
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

int begin()
{
  int fd = 0;
  char *fileName = "/dev/i2c-1";

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

int setSpeed(unsigned char value){
  int fd = begin();
  i2cWriteByteData(fd, COOLER_COMMAND, value);
  close (fd);
  return fd ;
}