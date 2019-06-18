#include "mbed.h"
//#include "mb.h"
#include "MPU9255.h"

void grafcet();
void grafcet1();


int gra_start, gra_read, gra_filter, gra_euler, gra_MBTrans, gra1_i2c;
int X0, X1, X2, X3, X4, X10, X11, X12;

/*9-axis*/
Serial pc(SERIAL_TX, SERIAL_RX);
I2C i2csda(I2C_SDA, I2C_SCL);
I2C i2csda_2(I2C2_SDA, I2C2_SCL);
MPU9255 mpu9255(&i2csda, true);
//MPU9255 mpu9255_1(&i2csda_2, true);	//&i2csda_2
//MPU9255 mpu9255(&i2csda_2, true);	//&i2csda_2

DigitalOut led(LED1);
Timer t;

int main()
{

    X0 = 1;

    pc.baud(9600);
    i2csda.frequency(400000);  // use fast (400 kHz) I2C  
		i2csda_2.frequency(400000);
    t.start();
    mpu9255.setting();
		//mpu9255_1.setting();

    while (1)
    {
        grafcet();
        wait(0.3);
    }

}

void grafcet()
{
    if (X0 && gra_start)
    {
        X0 = 0, X1 = 1, X10 = 1;
    }
    else if (X1 && X10)
    {
        grafcet1();
    }
    else if (X11 && gra_read)
    {
        X11 = 0, X1 = 0, X2 = 1;
    }
    else if (X2 && gra_filter)
    {
        X2 = 0, X3 = 1;
    }
    else if (X3 && gra_euler)
    {
        X3 = 0, X4 = 1;
    }
    else if (X4 && gra_MBTrans)
    {
        X4 = 0, X0 = 1;
    }
    //printf("X0 = %d , X1 = %d , X2 = %d , X3 = %d, X4 = %d, X10 = %d, X11 = %d\r\n", X0, X1, X2, X3, X4, X10, X11);
    //mpu9255.PrintSensorValue();

    mpu9255.SensorFusion();
		//mpu9255_1.SensorFusion();
}

void grafcet1()
{
    if (X10 && gra1_i2c)
    {
        X10 = 0, X11 = 1;
    }
}



