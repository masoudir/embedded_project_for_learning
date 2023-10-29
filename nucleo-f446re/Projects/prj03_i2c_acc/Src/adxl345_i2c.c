#include "adxl345_i2c.h"


extern I2C_HandleTypeDef hi2c1;

bool adxl345_i2c_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();

      /*Configure GPIO pin : PB12 */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);


    
    if(ADXL345_DEV_ID == adxl345_i2c_read_devid()) {
        adxl345_i2c_enable_measurement();
        return true;
    }

    return false;
}

uint8_t adxl345_i2c_read_devid() {
    ADXL345_I2C_ADDRESS_t addr = {
        .B = {
            .read_or_write = ADXL345_I2C_CMD_READ,
            .slave_address = ADXL345_I2C_ALTADDR_LOW
        }
    };
 

    uint8_t d = 0;

    HAL_I2C_Mem_Read(&hi2c1, (uint16_t)addr.R, ACC_REG_DEVID, 1, &d, 1, 100);
    printf("\nDEVID=%d\r\n", d);
    return d;
}

void adxl345_i2c_enable_measurement() {
    ADXL345_REG_POWER_CTL_t reg = {
        .B = {
            .WAKEUP = 0,
            .SLEEP = 0,
            .MEASURE = ADXL345_MEASUREMENT_ENABLED,
            .AUTO_SLEEP = 0,
            .LINK = 0,
            .RESERVED = 0
        }
    };

    ADXL345_I2C_ADDRESS_t addr = {
        .B = {
            .read_or_write = ADXL345_I2C_CMD_WRITE,
            .slave_address = ADXL345_I2C_ALTADDR_LOW
        }
    };

    HAL_I2C_Mem_Write(&hi2c1, (uint16_t)addr.R, ACC_REG_POWER_CTL, 1, &reg.R, 1, 100);
}

int ACC_CalculateOutputToIntegerFormat(uint16_t input, uint8_t number_of_bits) {
    uint16_t mask = 1 << (number_of_bits - 1);  // 0b100
    int output = 0;
    
    if((input & mask) != 0) {
        output = input & (~(mask));
        
        output -= (1 << (number_of_bits - 1));
    } else {
        output = input;
    }
    return output;
}


int16_t adxl345_get_acc_x() {

    ADXL345_I2C_ADDRESS_t addr = {
        .B = {
            .read_or_write = ADXL345_I2C_CMD_READ,
            .slave_address = ADXL345_I2C_ALTADDR_LOW
        }
    };
 

    uint8_t x[2] = {0};

    HAL_I2C_Mem_Read(&hi2c1, (uint16_t)addr.R, ACC_REG_DATAX0, 1, &x[0], 1, 100);
    HAL_I2C_Mem_Read(&hi2c1, (uint16_t)addr.R, ACC_REG_DATAX1, 1, &x[1], 1, 100);
    

    uint16_t output = ((x[1] << 8) | x[0]) & 0x1fff;

    int final_output = ACC_CalculateOutputToIntegerFormat(output, 13);

    printf("x0=%d x1=%d\r\n X=%d", x[0], x[1], final_output);

    return final_output;
    
}