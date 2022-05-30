                                                              
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include "si5351_70386.h" \\ change2 


#define I2C_FNAME       "/dev/i2c-0"
#define SI5351_ADDR     0x60

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
int
main()
{
        i2c_init();
        i2c_write(3, 0xFF);
        i2c_read(3);
        
        u_int8_t p90;
        p90 = 0.5 + 1.0/(4.0 * Fout) * (4.0 * Fvco);
        for (int i = 16; i <= 23; i++)
        {
                i2c_write(i, 0x80);
        }
        for (int i = 0; i < 52; i++)
        {
                i2c_write(si5351a_revb_registers[i].address ,si5351a_revb_registers[i].value);
        }
        i2c_write(177,0xAC);
        i2c_write(3, ~0x3); // step 7: makes all values at reg 3 outputs (since it is input when 0)
        i2c_write(166, p90);// change the clock phase  
}


