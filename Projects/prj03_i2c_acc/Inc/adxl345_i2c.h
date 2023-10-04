#ifndef __ADXL345_I2C_H
#define __ADXL345_I2C_H

#include "main.h"
#include <stdbool.h>

#define ADXL345_DEV_ID 0xE5

typedef enum {
    ADXL345_MEASUREMENT_DISABLED = 0,
    ADXL345_MEASUREMENT_ENABLED = 1
} ADXL345_EnableMeasurement_t;

typedef enum {
    ADXL345_I2C_ALTADDR_HIGH = 0x1D,
    ADXL345_I2C_ALTADDR_LOW = 0x53
} ADXL345_I2C_SlaveAddress_t;

typedef enum {
    ADXL345_I2C_CMD_WRITE = 0,
    ADXL345_I2C_CMD_READ = 1
} ADXL345_I2C_CMD_TYPE_t;


typedef union
  {
    uint8_t R;
    struct
    {
        bool read_or_write : 1;
        uint8_t slave_address : 7;
    } B;                 
} ADXL345_I2C_ADDRESS_t;



typedef union
  {
    uint8_t R;
    struct
    {
        uint8_t WAKEUP : 2;
        bool SLEEP : 1;
        bool MEASURE : 1;
        bool AUTO_SLEEP : 1;
        bool LINK : 1;
        uint8_t RESERVED : 2;
    } B;                 
} ADXL345_REG_POWER_CTL_t;

typedef enum
  {
    ACC_REG_DEVID = 0x00,
    ACC_REG_THRESH_TAP = 0x1D,
    ACC_REG_OFSX = 0x1E,
    ACC_REG_OFSY = 0x1F,
    ACC_REG_OFSZ = 0x20,
    ACC_REG_DUR = 0x21,
    ACC_REG_LATENT = 0x22,
    ACC_REG_WINDOW = 0x23,
    ACC_REG_THRESH_ACT = 0x24,
    ACC_REG_THRESH_INACT = 0x25,
    ACC_REG_TIME_INACT = 0x26,
    ACC_REG_ACT_INACT_CTL = 0x26,
    ACC_REG_THRESH_FF = 0x28,
    ACC_REG_TIME_FF = 0x29,
    ACC_REG_TAP_AXES = 0x2A,
    ACC_REG_ACT_TAP_STATUS = 0x2B,
    ACC_REG_BW_RATE = 0x2C,
    ACC_REG_POWER_CTL = 0x2D,
    ACC_REG_INT_ENABLE = 0x2E,
    ACC_REG_INT_MAP = 0x2F,
    ACC_REG_INT_SOURCE = 0x30,
    ACC_REG_DATA_FORMAT = 0x31,
    ACC_REG_DATAX0 = 0x32,
    ACC_REG_DATAX1 = 0x33,
    ACC_REG_DATAY0 = 0x34,
    ACC_REG_DATAY1 = 0x35,
    ACC_REG_DATAZ0 = 0x36,
    ACC_REG_DATAZ1 = 0x37,
    ACC_REG_FIFO_CTL = 0x38,
    ACC_REG_FIFO_STATUS = 0x39
  } ACC_SPI_REG_ADDR_t;


bool adxl345_i2c_init();
uint8_t adxl345_i2c_read_devid();
void adxl345_i2c_enable_measurement();
int16_t adxl345_get_acc_x();

#endif