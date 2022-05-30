#include <inttypes.h>
#include "si5351a.h"
#define I2C_WRITE 0b11000000            // I2C address for writing to the Si5351A
#define I2C_READ  0b11000001            // I2C address for reading to the Si5351A
typedef u_int32_t uint32_t;
typedef u_int8_t uint8_t;
//bruh
//
int     i2c_file;
void i2c_init()
{
        i2c_file = open(I2C_FNAME, O_RDWR);
        if (i2c_file < 0)
    {
        perror(I2C_FNAME);
                exit(1);
    }
}

int i2c_read(unsigned char reg)
{
        if (ioctl(i2c_file, I2C_SLAVE, SI5351_ADDR) < 0) 
    {
        perror(I2C_FNAME);
                exit(1);
    }

        int res;

        /* Using SMBus commands */
        res = i2c_smbus_read_byte_data(i2c_file, reg);
        if (res < 0) 
                exit(1);
        else 
                printf("r dev(0x%x) reg(0x%x)=0x%x (decimal %d)\n", SI5351_ADDR, reg, res, res);
        return res;
}
void i2c_write(unsigned char reg, unsigned char value)
{
        if (ioctl(i2c_file, I2C_SLAVE, SI5351_ADDR) < 0) 
    {
        perror(I2C_FNAME);
                exit(1);
    }

        int res;

}
// refresh all register
int main(int argc, char* argv[])
{
  int nfout;
  char * s = argv[argc - 1];
  sscanf(s, "%d", nfout);
  
  i2c_init();
  //i2c_write(3, 0xFF);
  //i2c_read(3);
   
  for (int i = 16; i <= 23; i++)
  {
          i2c_write(i, 0x80);
  }
  si5351aSetFrequency(nfout);
  i2c_write(177,0xAC);
  i2c_write(3, ~0x3); // step 7: makes all values at reg 3 outputs (since it is input when 0)

}