#ifndef MPU9255_H
#define MPU9255_H

#include "mbed.h"
#include "math.h"
DigitalOut LED_Red(LED3);
DigitalOut LED_Yellow(LED1);
int iTimes=0;
double  dIni_Yaw, dIni_Pitch, dIni_Roll;
// See also MPU-9255 Register Map and Descriptions, Revision 4.0, RM-MPU-9255A-00, Rev. 1.4, 9/9/2013 for registers not listed in 
// above document; the MPU9255 and MPU9150 are virtually identical but the latter has a different register map
//
//Magnetometer Registers
#define AK8963_ADDRESS   0x0C<<1
#define WHO_AM_I_AK8963  0x00 // should return 0x48
#define INFO             0x01
#define AK8963_ST1       0x02  // data ready status bit 0
#define AK8963_XOUT_L    0x03  // data
#define AK8963_XOUT_H    0x04
#define AK8963_YOUT_L    0x05
#define AK8963_YOUT_H    0x06
#define AK8963_ZOUT_L    0x07
#define AK8963_ZOUT_H    0x08
#define AK8963_ST2       0x09  // Data overflow bit 3 and data read error status bit 2
#define AK8963_CNTL      0x0A  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK8963_ASTC      0x0C  // Self test control
#define AK8963_I2CDIS    0x0F  // I2C disable
#define AK8963_ASAX      0x10  // Fuse ROM x-axis sensitivity adjustment value
#define AK8963_ASAY      0x11  // Fuse ROM y-axis sensitivity adjustment value
#define AK8963_ASAZ      0x12  // Fuse ROM z-axis sensitivity adjustment value

#define SELF_TEST_X_GYRO 0x00                  
#define SELF_TEST_Y_GYRO 0x01                                                                          
#define SELF_TEST_Z_GYRO 0x02

/*#define X_FINE_GAIN      0x03 // [7:0] fine gain
#define Y_FINE_GAIN      0x04
#define Z_FINE_GAIN      0x05
#define XA_OFFSET_H      0x06 // User-defined trim values for accelerometer
#define XA_OFFSET_L_TC   0x07
#define YA_OFFSET_H      0x08
#define YA_OFFSET_L_TC   0x09
#define ZA_OFFSET_H      0x0A
#define ZA_OFFSET_L_TC   0x0B */

#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E    
#define SELF_TEST_Z_ACCEL 0x0F

#define SELF_TEST_A      0x10

#define XG_OFFSET_H      0x13  // User-defined trim values for gyroscope
#define XG_OFFSET_L      0x14
#define YG_OFFSET_H      0x15
#define YG_OFFSET_L      0x16
#define ZG_OFFSET_H      0x17
#define ZG_OFFSET_L      0x18
#define SMPLRT_DIV       0x19
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define ACCEL_CONFIG2    0x1D
#define LP_ACCEL_ODR     0x1E   
#define WOM_THR          0x1F   

#define MOT_DUR          0x20  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
#define ZMOT_THR         0x21  // Zero-motion detection threshold bits [7:0]
#define ZRMOT_DUR        0x22  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms

#define FIFO_EN          0x23
#define I2C_MST_CTRL     0x24   
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35
#define I2C_MST_STATUS   0x36
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define DMP_INT_STATUS   0x39  // Check DMP interrupt
#define INT_STATUS       0x3A
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define MOT_DETECT_STATUS 0x61
#define I2C_SLV0_DO      0x63
#define I2C_SLV1_DO      0x64
#define I2C_SLV2_DO      0x65
#define I2C_SLV3_DO      0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define MOT_DETECT_CTRL  0x69
#define USER_CTRL        0x6A  // Bit 7 enable DMP, bit 3 reset DMP
#define PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
#define PWR_MGMT_2       0x6C
#define DMP_BANK         0x6D  // Activates a specific bank in the DMP
#define DMP_RW_PNT       0x6E  // Set read/write pointer to a specific start address in specified DMP bank
#define DMP_REG          0x6F  // Register in DMP from which to read or to which to write
#define DMP_REG_1        0x70
#define DMP_REG_2        0x71 
#define FIFO_COUNTH      0x72
#define FIFO_COUNTL      0x73
#define FIFO_R_W         0x74
#define WHO_AM_I_MPU9255 0x75 // Should return 0x71
#define XA_OFFSET_H      0x77
#define XA_OFFSET_L      0x78
#define YA_OFFSET_H      0x7A
#define YA_OFFSET_L      0x7B
#define ZA_OFFSET_H      0x7D
#define ZA_OFFSET_L      0x7E
#define size 12

// Using the MSENSR-9255 breakout board, ADO is set to 0 
// Seven-bit device address is 110100 for ADO = 0 and 110101 for ADO = 1
//mbed uses the eight-bit device address, so shift seven-bit addresses left by one!
#define ADO 0
#if ADO
#define MPU9255_ADDRESS 0x69<<1  // Device address when ADO = 1
#else
#define MPU9255_ADDRESS 0x68<<1  // Device address when ADO = 0
#endif
#define MPU9255_ADDRESS_MASTER 0x68<<1
#define MPU9255_ADDRESS_SLAVE 0x69<<1

// Set initial input parameters
enum Ascale {
    AFS_2G = 0,
    AFS_4G,
    AFS_8G,
    AFS_16G
};

enum Gscale {
    GFS_250DPS = 0,
    GFS_500DPS,
    GFS_1000DPS,
    GFS_2000DPS
};

enum Mscale {
    MFS_14BITS = 0, // 0.6 mG per LSB
    MFS_16BITS      // 0.15 mG per LSB
};

enum Mmode {
    MGT_8HZ = 0x02,		//8 Hz
    MGT_100HZ = 0x06	//100 Hz
};

enum Smplrt_div {
    SMPLRT_DIV_1000Hz = 0x00,
    SMPLRT_DIV_500Hz, // = 0x01,
    SMPLRT_DIV_333Hz, // = 0x02,
    SMPLRT_DIV_250Hz, // = 0x03,
    SMPLRT_DIV_200Hz, // = 0x04,
    SMPLRT_DIV_166Hz, // = 0x05,
    SMPLRT_DIV_142Hz, // = 0x06,
    SMPLRT_DIV_125Hz 	//= 0x07
};

uint8_t Ascale = AFS_2G;     // AFS_2G, AFS_4G, AFS_8G, AFS_16G
uint8_t Gscale = GFS_250DPS; // GFS_250DPS, GFS_500DPS, GFS_1000DPS, GFS_2000DPS
uint8_t Mscale = MFS_16BITS; // MFS_14BITS or MFS_16BITS, 14-bit or 16-bit magnetometer resolution
uint8_t Mmode = MGT_100HZ;   // Either 8 Hz 0x02) or 100 Hz (0x06) magnetometer data ODR 
uint8_t Smplrt_div = SMPLRT_DIV_200Hz;	 //sample_rate = Internal_Sample_Rate / (1 + SMPLRT_DIV)

float aRes, gRes, mRes;      // scale resolutions per LSB for the sensors

extern I2C i2csda, i2csda_2;
extern Serial pc;
extern DigitalOut led;
extern Timer t;
extern int gra_start, gra_read, gra_filter, gra_euler, gra_MBTrans, gra1_i2c;
extern int X0, X1, X2, X3, X4, X10, X11, X12;


int Initial = 1, ready = 0;

float magCalibration[3] = { 0, 0, 0 }, magbias[3] = { 0, 0, 0 };  // Factory mag calibration and mag bias
float gyroBias[3] = { 0, 0, 0 }, accelBias[3] = { 0, 0, 0 }; // Bias corrections for gyro and accelerometer
float SelfTest[6];

int delt_t = 0; // used to control display output rate
int count = 0;  // used to control display output rate

// parameters for 6 DoF sensor fusion calculations
float PI = 3.14159265358979323846f;
float GyroMeasError = PI * (60.0f / 180.0f);     // gyroscope measurement error in rads/s (start at 60 deg/s), then reduce after ~10 s to 3
float beta = sqrt(3.0f / 4.0f) * GyroMeasError;  // compute beta
float GyroMeasDrift = PI * (1.0f / 180.0f);      // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
float zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;  // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
#define Kp 2.0f * 5.0f // these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
#define Ki 0.0f

int lastUpdate = 0, firstUpdate = 0, Now = 0;    // used to calculate integration interval                               // used to calculate integration interval
float q[4] = { 1.0f, 0.0f, 0.0f, 0.0f };           // vector to hold quaternion
float eInt[3] = { 0.0f, 0.0f, 0.0f };              // vector to hold integral error for Mahony method

// System constants
#define gyroMeasError 3.14159265358979f * (5.0f / 180.0f)     // gyroscope measurement error in rad/s (shown as 5 deg/s)
#define beta sqrt(3.0f / 4.0f) * gyroMeasError                // compute beta
// Global system variables
float SEq_1 = 1.0f, SEq_2 = 0.0f, SEq_3 = 0.0f, SEq_4 = 0.0f; // estimated orientation quaternion elements with initial conditions
float ax, ay, az, gx, gy, gz, mx, my, mz, temperature; // variables to hold latest sensor data values
float yaw, pitch, roll;

class MPU9255 {
private:
    float sample_rate;
    I2C* m_i2c_obj;
    unsigned char m_mpu_address;
protected:
public:
    MPU9255(I2C* i2c_obj, const bool& flag)
        : m_i2c_obj(i2c_obj), m_mpu_address(flag ? MPU9255_ADDRESS_MASTER : MPU9255_ADDRESS_SLAVE)
    {

    };
    //===================================================================================================================
    //====== Set of useful function to access acceleratio, gyroscope, and temperature data
    //===================================================================================================================
    uint8_t whoami() {
        return readByte(m_mpu_address, WHO_AM_I_MPU9255);
    }

    void setEulerAngleSampleRate(float sr) {
        sample_rate = sr;
    }

    float getEulerAngleSampleRate() {
        return sample_rate;
    }

    void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
    {
        char data_write[2];
        data_write[0] = subAddress;
        data_write[1] = data;
        m_i2c_obj->write(address, data_write, 2, 0);
    }

    char readByte(uint8_t address, uint8_t subAddress)
    {
        if (X10 || Initial || ready)
        {
            gra1_i2c = 1;
        }
        if ((X11 && gra1_i2c) || Initial || ready)
        {
            char data[1]; // `data` will store the register data     
            char data_write[1];
            data_write[0] = subAddress;
            m_i2c_obj->write(address, data_write, 1, 1); // no stop
            m_i2c_obj->read(address, data, 1, 0);
            return data[0];
        }
    }

    void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
    {
        if (X10 || Initial || ready)
        {
            gra1_i2c = 1;
        }
        if ((X11 && gra1_i2c) || Initial || ready)
        {
            char data[14];
            char data_write[1];
            data_write[0] = subAddress;
            m_i2c_obj->write(address, data_write, 1, 1); // no stop
            m_i2c_obj->read(address, data, count, 0);
            for (int ii = 0; ii < count; ii++) {
                dest[ii] = data[ii];
            }
        }
    }

    void getRes() {

        getAres(); // Get accelerometer sensitivity
        getGres(); // Get gyro sensitivity
        getMres(); // Get magnetometer sensitivity
        //pc.printf("Accelerometer sensitivity is %f LSB/g \n\r", 1.0f/aRes);
        //pc.printf("Gyroscope sensitivity is %f LSB/deg/s \n\r", 1.0f/gRes);
        //pc.printf("Magnetometer sensitivity is %f LSB/G \n\r", 1.0f/mRes);
        magbias[0] = +470.;  // User environmental x-axis correction in milliGauss, should be automatically calculated
        magbias[1] = +120.;  // User environmental y-axis correction in milliGauss
        magbias[2] = +125.;  // User environmental z-axis correction in milliGauss
    }

    void getMres() {
        switch (Mscale)
        {
            // Possible magnetometer scales (and their register bit settings) are:
            // 14 bit resolution (0) and 16 bit resolution (1)
        case MFS_14BITS:
            mRes = 10.0*4219.0 / 8190.0; // Proper scale to return milliGauss
            break;
        case MFS_16BITS:
            //-32768~32767 * 10.0*4219.0/32760.0=> -42200~42200
            mRes = 10.0*4219.0 / 32760.0; // Proper scale to return milliGauss
            break;
        }
    }

    void getGres() {
        switch (Gscale)
        {
            // Possible gyro scales (and their register bit settings) are:
            // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11). 
            // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
        case GFS_250DPS:
            gRes = 250.0 / 32768.0;
            break;
        case GFS_500DPS:
            gRes = 500.0 / 32768.0;
            break;
        case GFS_1000DPS:
            gRes = 1000.0 / 32768.0;
            break;
        case GFS_2000DPS:
            gRes = 2000.0 / 32768.0;
            break;
        }
    }

    void getAres() {
        switch (Ascale)
        {
            // Possible accelerometer scales (and their register bit settings) are:
            // 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11). 
                // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
        case AFS_2G:
            aRes = 2.0 / 32768.0;
            break;
        case AFS_4G:
            aRes = 4.0 / 32768.0;
            break;
        case AFS_8G:
            aRes = 8.0 / 32768.0;
            break;
        case AFS_16G:
            aRes = 16.0 / 32768.0;
            break;
        }
    }

    void readAccelData(float *ax, float *ay, float *az)
    {
        int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
        uint8_t rawData[6];  // x/y/z accel register data stored here

        readBytes(m_mpu_address, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array

        if (X11 && gra1_i2c)
        {
            accelCount[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]);  // Turn the MSB and LSB into a signed 16-bit value
            accelCount[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
            accelCount[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);

            // Now we'll calculate the accleration value into actual g's
            *ax = (float)accelCount[0] * aRes - accelBias[0];  // get actual g value, this depends on scale being set
            *ay = (float)accelCount[1] * aRes - accelBias[1];
            *az = (float)accelCount[2] * aRes - accelBias[2];
        }
    }

    void readGyroData(float *gx, float *gy, float *gz)
    {
        int16_t gyroCount[3]; // Stores the 16-bit signed gyro sensor output
        uint8_t rawData[6];   // x/y/z gyro register data stored here

        readBytes(m_mpu_address, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array

        if (X11 && gra1_i2c)
        {
            gyroCount[0] = (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]);  // Turn the MSB and LSB into a signed 16-bit value
            gyroCount[1] = (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
            gyroCount[2] = (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
            // Calculate the gyro value into actual degrees per second
            *gx = (float)gyroCount[0] * gRes - gyroBias[0];  // get actual gyro value, this depends on scale being set
            *gy = (float)gyroCount[1] * gRes - gyroBias[1];
            *gz = (float)gyroCount[2] * gRes - gyroBias[2];
        }
    }

    void readMagData(float *mx, float *my, float *mz)
    {
        int16_t magCount[3]; // Stores the 16-bit signed magnetometer sensor output
        uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition

        if (readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
            readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
            uint8_t c = rawData[6]; // End data read by reading ST2 register
            if (!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
                magCount[0] = (int16_t)(((int16_t)rawData[1] << 8) | rawData[0]);  // Turn the MSB and LSB into a signed 16-bit value
                magCount[1] = (int16_t)(((int16_t)rawData[3] << 8) | rawData[2]);  // Data stored as little Endian
                magCount[2] = (int16_t)(((int16_t)rawData[5] << 8) | rawData[4]);
                // Calculate the magnetometer values in milliGauss
                // Include factory calibration per data sheet and user environmental corrections
                //mRes = -42200~42200 for 16 bit ADC
                //magCalibration = 0.5 ~ 1.5
                //magCount = -32768~32767
                *mx = (float)magCount[0] * mRes*magCalibration[0] - magbias[0];  // get actual magnetometer value, this depends on scale being set
                *my = (float)magCount[1] * mRes*magCalibration[1] - magbias[1];
                *mz = (float)magCount[2] * mRes*magCalibration[2] - magbias[2];
            }
        }
    }

    float readTempData()
    {
        int16_t tempCount;   // Stores the real internal chip temperature in degrees Celsius
        uint8_t rawData[2];  // x/y/z gyro register data stored here
        readBytes(m_mpu_address, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array 
        tempCount = (int16_t)(((int16_t)rawData[0]) << 8 | rawData[1]); // Turn the MSB and LSB into a 16-bit value
        return ((float)tempCount) / 333.87f + 21.0f;  // Temperature in degrees Centigrade
    }

    void resetMPU9255() {
        // reset device
        writeByte(m_mpu_address, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
        wait(0.1);
    }

    void initAK8963(float * destination) {
        // First extract the factory calibration for each magnetometer axis
        uint8_t rawData[3];  // x/y/z gyro calibration data stored here
        writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer  
        wait(0.01);
        writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
        wait(0.01);
        readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values

        //-0.5~0.5 + 1.0 => 0.5 ~ 1.5
        destination[0] = (float)(rawData[0] - 128) / 256.0f + 1.0f;   // Return x-axis sensitivity adjustment values, etc.
        destination[1] = (float)(rawData[1] - 128) / 256.0f + 1.0f;
        destination[2] = (float)(rawData[2] - 128) / 256.0f + 1.0f;
        writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer  
        wait(0.01);
        // Configure the magnetometer for continuous read and highest resolution
        // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
        // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
        writeByte(AK8963_ADDRESS, AK8963_CNTL, Mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR
        wait(0.01);
    }

    void initMPU9255() {
        // Initialize MPU9255 device
        // wake up device
        writeByte(m_mpu_address, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors 
        wait(0.1); // Delay 100 ms for PLL to get established on x-axis gyro; should check for PLL ready interrupt  

        // get stable time source
        writeByte(m_mpu_address, PWR_MGMT_1, 0x01);  // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001

        // Configure Gyro and Accelerometer
        // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively; 
        // DLPF_CFG = bits 2:0 = 010; this sets the sample rate at 1 kHz for both
        // Maximum delay is 4.9 ms which is just over a 200 Hz maximum rate
        writeByte(m_mpu_address, CONFIG, 0x03);

        // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
        writeByte(m_mpu_address, SMPLRT_DIV, Smplrt_div);  // Use a 200 Hz rate; the same rate set in CONFIG above

        // Set gyroscope full scale range
        // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
        uint8_t c = readByte(m_mpu_address, GYRO_CONFIG);
        writeByte(m_mpu_address, GYRO_CONFIG, c & ~0xE0); // Clear self-test bits [7:5] 
        writeByte(m_mpu_address, GYRO_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
        writeByte(m_mpu_address, GYRO_CONFIG, c | Gscale << 3); // Set full scale range for the gyro

        // Set accelerometer configuration
        c = readByte(m_mpu_address, ACCEL_CONFIG);
        writeByte(m_mpu_address, ACCEL_CONFIG, c & ~0xE0); // Clear self-test bits [7:5] 
        writeByte(m_mpu_address, ACCEL_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
        writeByte(m_mpu_address, ACCEL_CONFIG, c | Ascale << 3); // Set full scale range for the accelerometer 

        // Set accelerometer sample rate configuration
        // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
        // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
        c = readByte(m_mpu_address, ACCEL_CONFIG2);
        writeByte(m_mpu_address, ACCEL_CONFIG2, c & ~0x0F); // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])  
        writeByte(m_mpu_address, ACCEL_CONFIG2, c | 0x03); // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz

        // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates, 
        // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

        // Configure Interrupts and Bypass Enable
        // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips 
        // can join the I2C bus and all can be controlled by the Arduino as master
        writeByte(m_mpu_address, INT_PIN_CFG, 0x22);
        writeByte(m_mpu_address, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
    }

    // Function which accumulates gyro and accelerometer data after device initialization. It calculates the average
    // of the at-rest readings and then loads the resulting offsets into accelerometer and gyro bias registers.
    void calibrateMPU9255(float * dest1, float * dest2)
    {
        uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
        uint16_t ii, packet_count, fifo_count;
        int32_t gyro_bias[3] = { 0, 0, 0 }, accel_bias[3] = { 0, 0, 0 };

        // reset device, reset all registers, clear gyro and accelerometer bias registers
        writeByte(m_mpu_address, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
        wait(0.1);

        // get stable time source
        // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
        writeByte(m_mpu_address, PWR_MGMT_1, 0x01);
        writeByte(m_mpu_address, PWR_MGMT_2, 0x00);
        wait(0.2);

        // Configure device for bias calculation
        writeByte(m_mpu_address, INT_ENABLE, 0x00);   // Disable all interrupts
        writeByte(m_mpu_address, FIFO_EN, 0x00);      // Disable FIFO
        writeByte(m_mpu_address, PWR_MGMT_1, 0x00);   // Turn on internal clock source
        writeByte(m_mpu_address, I2C_MST_CTRL, 0x00); // Disable I2C master
        writeByte(m_mpu_address, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
        writeByte(m_mpu_address, USER_CTRL, 0x0C);    // Reset FIFO and DMP
        wait(0.015);

        // Configure MPU9255 gyro and accelerometer for bias calculation
        writeByte(m_mpu_address, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
        writeByte(m_mpu_address, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
        writeByte(m_mpu_address, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
        writeByte(m_mpu_address, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

        uint16_t  gyrosensitivity = 131;   // = 131 LSB/degrees/sec
        uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g

        // Configure FIFO to capture accelerometer and gyro data for bias calculation
        writeByte(m_mpu_address, USER_CTRL, 0x40);   // Enable FIFO  
        writeByte(m_mpu_address, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO (max size 512 bytes in MPU-9255)
        wait(0.04); // accumulate 40 samples in 80 milliseconds = 480 bytes

        // At end of sample accumulation, turn off FIFO sensor read
        writeByte(m_mpu_address, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
        readBytes(m_mpu_address, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
        fifo_count = ((uint16_t)data[0] << 8) | data[1];
        packet_count = fifo_count / 12;// How many sets of full gyro and accelerometer data for averaging

        for (ii = 0; ii < packet_count; ii++) {
            int16_t accel_temp[3] = { 0, 0, 0 }, gyro_temp[3] = { 0, 0, 0 };
            readBytes(m_mpu_address, FIFO_R_W, 12, &data[0]); // read data for averaging
            accel_temp[0] = (int16_t)(((int16_t)data[0] << 8) | data[1]);  // Form signed 16-bit integer for each sample in FIFO
            accel_temp[1] = (int16_t)(((int16_t)data[2] << 8) | data[3]);
            accel_temp[2] = (int16_t)(((int16_t)data[4] << 8) | data[5]);
            gyro_temp[0] = (int16_t)(((int16_t)data[6] << 8) | data[7]);
            gyro_temp[1] = (int16_t)(((int16_t)data[8] << 8) | data[9]);
            gyro_temp[2] = (int16_t)(((int16_t)data[10] << 8) | data[11]);

            accel_bias[0] += (int32_t)accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
            accel_bias[1] += (int32_t)accel_temp[1];
            accel_bias[2] += (int32_t)accel_temp[2];
            gyro_bias[0] += (int32_t)gyro_temp[0];
            gyro_bias[1] += (int32_t)gyro_temp[1];
            gyro_bias[2] += (int32_t)gyro_temp[2];
        }
        accel_bias[0] /= (int32_t)packet_count; // Normalize sums to get average count biases
        accel_bias[1] /= (int32_t)packet_count;
        accel_bias[2] /= (int32_t)packet_count;
        gyro_bias[0] /= (int32_t)packet_count;
        gyro_bias[1] /= (int32_t)packet_count;
        gyro_bias[2] /= (int32_t)packet_count;

        if (accel_bias[2] > 0L) { accel_bias[2] -= (int32_t)accelsensitivity; }  // Remove gravity from the z-axis accelerometer bias calculation
        else { accel_bias[2] += (int32_t)accelsensitivity; }

        // Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
        data[0] = (-gyro_bias[0] / 4 >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
        data[1] = (-gyro_bias[0] / 4) & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
        data[2] = (-gyro_bias[1] / 4 >> 8) & 0xFF;
        data[3] = (-gyro_bias[1] / 4) & 0xFF;
        data[4] = (-gyro_bias[2] / 4 >> 8) & 0xFF;
        data[5] = (-gyro_bias[2] / 4) & 0xFF;

        /// Push gyro biases to hardware registers
        /*  writeByte(m_mpu_address, XG_OFFSET_H, data[0]);
          writeByte(m_mpu_address, XG_OFFSET_L, data[1]);
          writeByte(m_mpu_address, YG_OFFSET_H, data[2]);
          writeByte(m_mpu_address, YG_OFFSET_L, data[3]);
          writeByte(m_mpu_address, ZG_OFFSET_H, data[4]);
          writeByte(m_mpu_address, ZG_OFFSET_L, data[5]);
        */
        dest1[0] = (float)gyro_bias[0] / (float)gyrosensitivity; // construct gyro bias in deg/s for later manual subtraction
        dest1[1] = (float)gyro_bias[1] / (float)gyrosensitivity;
        dest1[2] = (float)gyro_bias[2] / (float)gyrosensitivity;

        // Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
        // factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
        // non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
        // compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
        // the accelerometer biases calculated above must be divided by 8.

        int32_t accel_bias_reg[3] = { 0, 0, 0 }; // A place to hold the factory accelerometer trim biases
        readBytes(m_mpu_address, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
        accel_bias_reg[0] = (int16_t)((int16_t)data[0] << 8) | data[1];
        readBytes(m_mpu_address, YA_OFFSET_H, 2, &data[0]);
        accel_bias_reg[1] = (int16_t)((int16_t)data[0] << 8) | data[1];
        readBytes(m_mpu_address, ZA_OFFSET_H, 2, &data[0]);
        accel_bias_reg[2] = (int16_t)((int16_t)data[0] << 8) | data[1];

        uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
        uint8_t mask_bit[3] = { 0, 0, 0 }; // Define array to hold mask bit for each accelerometer bias axis

        for (ii = 0; ii < 3; ii++) {
            if (accel_bias_reg[ii] & mask) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
        }

        // Construct total accelerometer bias, including calculated average accelerometer bias from above
        accel_bias_reg[0] -= (accel_bias[0] / 8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
        accel_bias_reg[1] -= (accel_bias[1] / 8);
        accel_bias_reg[2] -= (accel_bias[2] / 8);

        data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
        data[1] = (accel_bias_reg[0]) & 0xFF;
        data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
        data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
        data[3] = (accel_bias_reg[1]) & 0xFF;
        data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
        data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
        data[5] = (accel_bias_reg[2]) & 0xFF;
        data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

    // Apparently this is not working for the acceleration biases in the MPU-9255
    // Are we handling the temperature correction bit properly?
    // Push accelerometer biases to hardware registers
    /*  writeByte(m_mpu_address, XA_OFFSET_H, data[0]);
      writeByte(m_mpu_address, XA_OFFSET_L, data[1]);
      writeByte(m_mpu_address, YA_OFFSET_H, data[2]);
      writeByte(m_mpu_address, YA_OFFSET_L, data[3]);
      writeByte(m_mpu_address, ZA_OFFSET_H, data[4]);
      writeByte(m_mpu_address, ZA_OFFSET_L, data[5]);
    */
    // Output scaled accelerometer biases for manual subtraction in the main program
        dest2[0] = (float)accel_bias[0] / (float)accelsensitivity;
        dest2[1] = (float)accel_bias[1] / (float)accelsensitivity;
        dest2[2] = (float)accel_bias[2] / (float)accelsensitivity;
    }

    // Accelerometer and gyroscope self test; check calibration wrt factory settings
    void MPU9255SelfTest(float * destination) // Should return percent deviation from factory trim values, +/- 14 or less deviation is a pass
    {
        uint8_t rawData[6] = { 0, 0, 0, 0, 0, 0 };
        uint8_t selfTest[6];
        int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
        float factoryTrim[6];
        uint8_t FS = 0;

        writeByte(m_mpu_address, SMPLRT_DIV, 0x00); // Set gyro sample rate to 1 kHz �����W�v
        writeByte(m_mpu_address, CONFIG, 0x02); // Set gyro sample rate to 1 kHz and DLPF to 92 Hz �C�W�o�i���I���W�v
        writeByte(m_mpu_address, GYRO_CONFIG, 1 << FS); // Set full scale range for the gyro to 250 dps 
        writeByte(m_mpu_address, ACCEL_CONFIG2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
        writeByte(m_mpu_address, ACCEL_CONFIG, 1 << FS); // Set full scale range for the accelerometer to 2 g

        for (int ii = 0; ii < 200; ii++) { // get average current values of gyro and acclerometer
            readBytes(m_mpu_address, ACCEL_XOUT_H, 6, &rawData[0]); // Read the six raw data registers into data array
            aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
            aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
            aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);

            readBytes(m_mpu_address, GYRO_XOUT_H, 6, &rawData[0]); // Read the six raw data registers sequentially into data array
            gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
            gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
            gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
        }

        for (int ii = 0; ii < 3; ii++) { // Get average of 200 values and store as average current readings
            aAvg[ii] /= 200;
            gAvg[ii] /= 200;
        }

        // Configure the accelerometer for self-test
        writeByte(m_mpu_address, ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
        writeByte(m_mpu_address, GYRO_CONFIG, 0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
        wait(0.25); // Delay a while to let the device stabilize

        for (int ii = 0; ii < 200; ii++) { // get average self-test values of gyro and acclerometer

            readBytes(m_mpu_address, ACCEL_XOUT_H, 6, &rawData[0]); // Read the six raw data registers into data array
            aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
            aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
            aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);

            readBytes(m_mpu_address, GYRO_XOUT_H, 6, &rawData[0]); // Read the six raw data registers sequentially into data array
            gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
            gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
            gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
        }

        for (int ii = 0; ii < 3; ii++) { // Get average of 200 values and store as average self-test readings
            aSTAvg[ii] /= 200;
            gSTAvg[ii] /= 200;
        }
        // Configure the gyro and accelerometer for normal operation
        writeByte(m_mpu_address, ACCEL_CONFIG, 0x00);
        writeByte(m_mpu_address, GYRO_CONFIG, 0x00);
        wait(0.25); // Delay a while to let the device stabilize

        // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
        selfTest[0] = readByte(m_mpu_address, SELF_TEST_X_ACCEL); // X-axis accel self-test results
        selfTest[1] = readByte(m_mpu_address, SELF_TEST_Y_ACCEL); // Y-axis accel self-test results
        selfTest[2] = readByte(m_mpu_address, SELF_TEST_Z_ACCEL); // Z-axis accel self-test results
        selfTest[3] = readByte(m_mpu_address, SELF_TEST_X_GYRO); // X-axis gyro self-test results
        selfTest[4] = readByte(m_mpu_address, SELF_TEST_Y_GYRO); // Y-axis gyro self-test results
        selfTest[5] = readByte(m_mpu_address, SELF_TEST_Z_GYRO); // Z-axis gyro self-test results

        // Retrieve factory self-test value from self-test code reads
        factoryTrim[0] = (float)(2620 / 1 << FS)*(pow(1.01f, ((float)selfTest[0] - 1.0f))); // FT[Xa] factory trim calculation
        factoryTrim[1] = (float)(2620 / 1 << FS)*(pow(1.01f, ((float)selfTest[1] - 1.0f))); // FT[Ya] factory trim calculation
        factoryTrim[2] = (float)(2620 / 1 << FS)*(pow(1.01f, ((float)selfTest[2] - 1.0f))); // FT[Za] factory trim calculation
        factoryTrim[3] = (float)(2620 / 1 << FS)*(pow(1.01f, ((float)selfTest[3] - 1.0f))); // FT[Xg] factory trim calculation
        factoryTrim[4] = (float)(2620 / 1 << FS)*(pow(1.01f, ((float)selfTest[4] - 1.0f))); // FT[Yg] factory trim calculation
        factoryTrim[5] = (float)(2620 / 1 << FS)*(pow(1.01f, ((float)selfTest[5] - 1.0f))); // FT[Zg] factory trim calculation

        // Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
        // To get percent, must multiply by 100
        for (int i = 0; i < 3; i++) {
            destination[i] = 100.0f*((float)(aSTAvg[i] - aAvg[i])) / factoryTrim[i]; // Report percent differences
            destination[i + 3] = 100.0f*((float)(gSTAvg[i] - gAvg[i])) / factoryTrim[i + 3]; // Report percent differences
        }

    }

    void initSensor(uint8_t smplrt_div, uint8_t mmode, uint8_t afs, uint8_t gfs, uint8_t mfs)
    {
        Smplrt_div = smplrt_div;
        Mmode = mmode;
        Ascale = afs;
        Gscale = gfs;
        Mscale = mfs;

        //software reset by setting register
        resetMPU9255(); // Reset registers to default in preparation for device calibration
        //self test
        MPU9255SelfTest(SelfTest); // Start by performing self test and reporting values
        calibrateMPU9255(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
        wait(2);

        initMPU9255();
        initAK8963(magCalibration);
        wait(1);

        //get resolution of MPU9255
        getRes();
    }

    void printInfo(Serial *pc)
    {
        pc->printf("\n\r--------------- start of Sensor Infomation ---------------\n\r");
        pc->printf("x-axis self test: acceleration trim within : %f % of factory value\n\r", SelfTest[0]);
        pc->printf("y-axis self test: acceleration trim within : %f % of factory value\n\r", SelfTest[1]);
        pc->printf("z-axis self test: acceleration trim within : %f % of factory value\n\r", SelfTest[2]);
        pc->printf("x-axis self test: gyration trim within : %f % of factory value\n\r", SelfTest[3]);
        pc->printf("y-axis self test: gyration trim within : %f % of factory value\n\r", SelfTest[4]);
        pc->printf("z-axis self test: gyration trim within : %f % of factory value\n\r", SelfTest[5]);

        pc->printf("x gyro bias = %f\n\r", gyroBias[0]);
        pc->printf("y gyro bias = %f\n\r", gyroBias[1]);
        pc->printf("z gyro bias = %f\n\r", gyroBias[2]);
        pc->printf("x accel bias = %f\n\r", accelBias[0]);
        pc->printf("y accel bias = %f\n\r", accelBias[1]);
        pc->printf("z accel bias = %f\n\r", accelBias[2]);

        pc->printf("MPU9255 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature

        pc->printf("AK8963 initialized for active data mode....\n\r"); // Initialize device for active mode read of magnetometer
        pc->printf("Accelerometer full-scale range = %f  g\n\r", 2.0f*(float)(1 << Ascale));
        pc->printf("Gyroscope full-scale range = %f  deg/s\n\r", 250.0f*(float)(1 << Gscale));
        if (Mscale == 0) pc->printf("Magnetometer resolution = 14  bits\n\r");
        else if (Mscale == 1) pc->printf("Magnetometer resolution = 16  bits\n\r");
        if (Mmode == 2) pc->printf("Magnetometer ODR = 8 Hz\n\r");
        else if (Mmode == 6) pc->printf("Magnetometer ODR = 100 Hz\n\r");
        pc->printf("Accelerometer and Gyroscope sampling rate = %d Hz\n\r", 1000 / (1 + Smplrt_div));

        pc->printf("--------------- end of Sensor Infomation ---------------\n\r");
    }

    bool isDataReady()
    {
        ready = 1;
        return readByte(m_mpu_address, INT_STATUS) & 0x01;
    }

    // Implementation of Sebastian Madgwick's "...efficient orientation filter for... inertial/magnetic sensor arrays"
    // (see http://www.x-io.co.uk/category/open-source/ for examples and more details)
    // which fuses acceleration and rotation rate to produce a quaternion-based estimate of relative
    // device orientation -- which can be converted to yaw, pitch, and roll. Useful for stabilizing quadcopters, etc.
    // The performance of the orientation filter is at least as good as conventional Kalman-based filtering algorithms
    // but is much less computationally intensive---it can be performed on a 3.3 V Pro Mini operating at 8 MHz!
    void filterUpdate(float gx, float gy, float gz, float ax, float ay, float az, float deltat)
    {
        // Local system variables
        float norm;                                                            // vector norm
        float SEqDot_omega_1, SEqDot_omega_2, SEqDot_omega_3, SEqDot_omega_4;  // quaternion derrivative from gyroscopes elements
        float f_1, f_2, f_3;                                                   // objective function elements
        float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33;              // objective function Jacobian elements
        float SEqHatDot_1, SEqHatDot_2, SEqHatDot_3, SEqHatDot_4;              // estimated direction of the gyroscope error
        // Axulirary variables to avoid reapeated calcualtions
        float halfSEq_1 = 0.5f * SEq_1;
        float halfSEq_2 = 0.5f * SEq_2;
        float halfSEq_3 = 0.5f * SEq_3;
        float halfSEq_4 = 0.5f * SEq_4;
        float twoSEq_1 = 2.0f * SEq_1;
        float twoSEq_2 = 2.0f * SEq_2;
        float twoSEq_3 = 2.0f * SEq_3;

        // Normalise the accelerometer measurement
        norm = sqrt(ax * ax + ay * ay + az * az);
        ax /= norm;
        ay /= norm;
        az /= norm;
        // Compute the objective function and Jacobian
        f_1 = twoSEq_2 * SEq_4 - twoSEq_1 * SEq_3 - ax;
        f_2 = twoSEq_1 * SEq_2 + twoSEq_3 * SEq_4 - ay;
        f_3 = 1.0f - twoSEq_2 * SEq_2 - twoSEq_3 * SEq_3 - az;
        J_11or24 = twoSEq_3;                                                    // J_11 negated in matrix multiplication
        J_12or23 = 2.0f * SEq_4;
        J_13or22 = twoSEq_1;                                                    // J_12 negated in matrix multiplication
        J_14or21 = twoSEq_2;
        J_32 = 2.0f * J_14or21;                                                 // negated in matrix multiplication
        J_33 = 2.0f * J_11or24;                                                 // negated in matrix multiplication
        // Compute the gradient (matrix multiplication)
        SEqHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1;
        SEqHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3;
        SEqHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1;
        SEqHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2;
        // Normalise the gradient
        norm = sqrt(SEqHatDot_1 * SEqHatDot_1 + SEqHatDot_2 * SEqHatDot_2 + SEqHatDot_3 * SEqHatDot_3 + SEqHatDot_4 * SEqHatDot_4);
        SEqHatDot_1 /= norm;
        SEqHatDot_2 /= norm;
        SEqHatDot_3 /= norm;
        SEqHatDot_4 /= norm;
        // Compute the quaternion derrivative measured by gyroscopes
        SEqDot_omega_1 = -halfSEq_2 * gx - halfSEq_3 * gy - halfSEq_4 * gz;
        SEqDot_omega_2 = halfSEq_1 * gx + halfSEq_3 * gz - halfSEq_4 * gy;
        SEqDot_omega_3 = halfSEq_1 * gy - halfSEq_2 * gz + halfSEq_4 * gx;
        SEqDot_omega_4 = halfSEq_1 * gz + halfSEq_2 * gy - halfSEq_3 * gx;
        // Compute then integrate the estimated quaternion derrivative
        SEq_1 += (SEqDot_omega_1 - (beta * SEqHatDot_1)) * deltat;
        SEq_2 += (SEqDot_omega_2 - (beta * SEqHatDot_2)) * deltat;
        SEq_3 += (SEqDot_omega_3 - (beta * SEqHatDot_3)) * deltat;
        SEq_4 += (SEqDot_omega_4 - (beta * SEqHatDot_4)) * deltat;
        // Normalise quaternion
        norm = sqrt(SEq_1 * SEq_1 + SEq_2 * SEq_2 + SEq_3 * SEq_3 + SEq_4 * SEq_4);
        SEq_1 /= norm;
        SEq_2 /= norm;
        SEq_3 /= norm;
        SEq_4 /= norm;
    }

    void getEulerDegreeFilter(float *yaw, float *pitch, float *roll)
    {

        // Define output variables from updated quaternion---these are Tait-Bryan angles, commonly used in aircraft orientation.
        // In this coordinate system, the positive z-axis is down toward Earth. 
        // Yaw is the angle between Sensor x-axis and Earth magnetic North (or true North if corrected for local declination, looking down on the sensor positive yaw is counterclockwise.
        // Pitch is angle between sensor x-axis and Earth ground plane, toward the Earth is positive, up toward the sky is negative.
        // Roll is angle between sensor y-axis and Earth ground plane, y-axis up is positive roll.
        // These arise from the definition of the homogeneous rotation matrix constructed from quaternions.
        // Tait-Bryan angles as well as Euler angles are non-commutative; that is, the get the correct orientation the rotations must be
        // applied in the correct order which for this configuration is yaw, pitch, and then roll.
        // For more see http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles which has additional links.
        *yaw = atan2(2.0f * (SEq_2 * SEq_3 + SEq_1 * SEq_4), SEq_1 * SEq_1 + SEq_2 * SEq_2 - SEq_3 * SEq_3 - SEq_4 * SEq_4);
        *pitch = -asin(2.0f * (SEq_2 * SEq_4 - SEq_1 * SEq_3));
        *roll = atan2(2.0f * (SEq_1 * SEq_2 + SEq_3 * SEq_4), SEq_1 * SEq_1 - SEq_2 * SEq_2 - SEq_3 * SEq_3 + SEq_4 * SEq_4);
        *pitch *= 180.0f / PI;
        *yaw *= 180.0f / PI;
        *yaw -= 13.8f; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
        *roll *= 180.0f / PI;

    }

    void PrintSensorValue()
    {
        //LED_Yellow =false;
			  LED_Red    =false;
			  //printf(" ax = %f  , ay = %f  , az = %f  g\n\r", ax, ay, az);
        
        //printf(" mx = %f, my = %f, mz = %f  mG\n\r", mx, my, mz);
        //Initial values
				if(iTimes==0)
				{
					dIni_Yaw=yaw;
					dIni_Pitch=pitch;
					dIni_Roll=roll;
				}
				iTimes++;

				printf("  ======================Times========================\n\r");
				printf("  %d times\r\n",iTimes);
				printf("  gx = %.2f, gy = %.2f, gz = %.2f  deg/s       \n\r", gx, gy, gz);
        printf("  Initial    (yaw, pitch, roll): %.2f %.2f %.2f \n\r", dIni_Yaw, dIni_Pitch, dIni_Roll);
        printf("  Orientation(yaw, pitch, roll): %.2f %.2f %.2f \n\r", yaw, pitch, roll);
        printf("  Difference (yaw, pitch, roll): %.2f %.2f %.2f \n\r", yaw-dIni_Yaw, pitch-dIni_Pitch, roll-dIni_Roll);		
				printf("  ======================Result=======================\n\r");	
			  if(pitch <= -40)
				{
					LED_Red = true;
					printf("  =                  Wrong posture                  =\n\r");					
				}
				else
				{
					//LED_Yellow =true;
					printf("  =                 Correct posture                 =\n\r");					
				}
        printf("  ===================================================  \n\r");
				printf("\r\n");				
    }

    void setting()
    {
        uint8_t Whoami = whoami();
        if (Whoami == 0x73) // WHO_AM_I should always be 0x68
        {
            initSensor(SMPLRT_DIV_500Hz, MGT_100HZ, AFS_2G, GFS_250DPS, MFS_16BITS);
            setEulerAngleSampleRate(500);	//in millisecond
            printInfo(&pc);
            Initial = 0;
        }
        else
        {
            printf("Could not connect to MPU9255: \n\r");
            printf("%x \n", Whoami);
            while (1);
        }
    }

    void SensorFusion()
    {
        float deltat = 0.0f;

        if (X0)
        {
            gra_start = 1;
        }

        if (X1)
        {
            gra_start = 0;
            if (isDataReady())
            {
                // On interrupt, check if data ready interrupt
                ready = 0;
                readAccelData(&ax, &ay, &az);  	// Read the accel x/y/z adc values  
                readGyroData(&gx, &gy, &gz);  	// Read the gyro x/y/z adc values
                readMagData(&mx, &my, &mz);  		// Read the mag x/y/z adc values   
                gra_read = 1; gra1_i2c = 0;
            }
        }

        Now = t.read_us();
        deltat = (float)((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
        lastUpdate = Now;
        temperature = readTempData();

        if (X2 && gra_read)
        {
            gra_read = 0, gra_filter = 1;
            if (gra_filter)
                filterUpdate(gx*PI / 180.0f, gy*PI / 180.0f, gz*PI / 180.0f, ax, ay, az, deltat);
        }

        delt_t = t.read_ms() - count;

        if (X3 && gra_filter)
        {
            gra_filter = 0, gra_euler = 1;
            if (gra_euler)
                getEulerDegreeFilter(&yaw, &pitch, &roll);
        }

        if (X4 && gra_euler)
        {
            gra_euler = 0; gra_MBTrans = 1;
            if (gra_MBTrans)
                PrintSensorValue();

        }
        count = t.read_ms();

        if (count > 1 << 21)
        {
            t.start(); // start the timer over again if ~30 minutes has passed
            count = 0;
            deltat = 0;
            lastUpdate = t.read_us();
        }
        led = !led;

    }

};





#endif

