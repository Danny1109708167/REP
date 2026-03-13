/**
 ******************************************************************************
 * @file    IIC.c
 * @author  Dario Liu
 * @brief   IIC Config
 ******************************************************************************
 * @attention
 */

/* Includes ------------------------------------------------------------------*/
#include "IIC.h"
#ifdef IIC_ENABLE
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef I2cHandle;
#define IIC_H I2cHandle
uint8_t reg_adr = 0;
uint8_t reg_data = 0;
uint8_t data_offset = 0;
uint8_t I2C_state = 0;
uint8_t data_count = 0;
extern uint8_t I2C_Noack;
extern uint8_t IIC_Restart;
extern uint32_t Catch_Time;

static uint8_t slave_data[] =
{
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
    0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
    0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
    // 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
    // 0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
    // 0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,
    // 0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
    // 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,
    // 0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
    // 0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,
    // 0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
    // 0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,
    // 0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
    // 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
    // 0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
    // 0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
    // 0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
    // 0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,
    // 0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
    // 0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,
    // 0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
    // 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,
    // 0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
    // 0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,
    // 0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
    // 0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,
    // 0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
    // 0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,
    // 0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
};

IIC_BUS iic_slave[] =
    {
        // {0x00, OR, Reg_8bit, (void *)&reg00},
        // {0x02, OR, Reg_16bit, (void*)&voltage},
        // {0x03, OR, Reg_8bit, (void *)&reg03},
        // {0x04, OR, Reg_16bit, (void*)&percentage},
        // {0x05, OR, Reg_8bit, (void *)&reg05},
        // {0x06, OR, Reg_8bit, (void *)&reg06},
        // {0x08, OR, Reg_8bit, (void *)&reg08},
        // {0x0B, OR, Reg_8bit, (void *)&reg0b},
        // {0x0E, OR, Reg_16bit, (void*)&electricity},

        // 0x00-0x0F
        {0x00, OR, Reg_8bit, (void *)&slave_data[0]},
        {0x01, OR, Reg_8bit, (void *)&slave_data[1]},
        {0x02, OR, Reg_8bit, (void *)&slave_data[2]},
        {0x03, OR, Reg_8bit, (void *)&slave_data[3]},
        {0x04, OR, Reg_8bit, (void *)&slave_data[4]},
        {0x05, OR, Reg_8bit, (void *)&slave_data[5]},
        {0x06, OR, Reg_8bit, (void *)&slave_data[6]},
        {0x07, OR, Reg_8bit, (void *)&slave_data[7]},
        {0x08, OR, Reg_8bit, (void *)&slave_data[8]},
        {0x09, OR, Reg_8bit, (void *)&slave_data[9]},
        {0x0A, OR, Reg_8bit, (void *)&slave_data[10]},
        {0x0B, OR, Reg_8bit, (void *)&slave_data[11]},
        {0x0C, OR, Reg_8bit, (void *)&slave_data[12]},
        {0x0D, OR, Reg_8bit, (void *)&slave_data[13]},
        {0x0E, OR, Reg_8bit, (void *)&slave_data[14]},
        {0x0F, OR, Reg_8bit, (void *)&slave_data[15]},

        // 0x10-0x1F
        {0x10, OW, Reg_8bit, (void *)&slave_data[16]},
        {0x11, OW, Reg_8bit, (void *)&slave_data[17]},
        {0x12, OW, Reg_8bit, (void *)&slave_data[18]},
        {0x13, OW, Reg_8bit, (void *)&slave_data[19]},
        {0x14, OW, Reg_8bit, (void *)&slave_data[20]},
        {0x15, OW, Reg_8bit, (void *)&slave_data[21]},
        {0x16, OW, Reg_8bit, (void *)&slave_data[22]},
        {0x17, OW, Reg_8bit, (void *)&slave_data[23]},
        {0x18, OW, Reg_8bit, (void *)&slave_data[24]},
        {0x19, OW, Reg_8bit, (void *)&slave_data[25]},
        {0x1A, OW, Reg_8bit, (void *)&slave_data[26]},
        {0x1B, OW, Reg_8bit, (void *)&slave_data[27]},
        {0x1C, OW, Reg_8bit, (void *)&slave_data[28]},
        {0x1D, OW, Reg_8bit, (void *)&slave_data[29]},
        {0x1E, OW, Reg_8bit, (void *)&slave_data[30]},
        {0x1F, OW, Reg_8bit, (void *)&slave_data[31]},

        {0x67, RW, Reg_8bit, (void *)&slave_data[32]}

        //  OW   logic
    };

void IIC_Config(void)
{
    IIC_H.Instance = I2C;                                 /* I2C */
    IIC_H.Init.ClockSpeed = I2C_SPEEDCLOCK;               /* I2C communication speed */
    IIC_H.Init.DutyCycle = I2C_DUTYCYCLE;                 /* I2C duty cycle */
    IIC_H.Init.OwnAddress1 = I2C_ADDRESS;                 /* I2C address */
    IIC_H.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE; /* Prohibit broadcast calls */
    IIC_H.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;     /* Allow clock extension */
    HAL_I2C_Init(&IIC_H);

    HAL_I2C_EnableListen_IT(&IIC_H);
    // HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, &reg_adr, 1, I2C_FIRST_AND_LAST_FRAME);
    // __HAL_I2C_ENABLE_IT(&IIC_H, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR);
    
    // NVIC_SetPriority(I2C_SCL_EXTI_IRQN, 0);
    // NVIC_EnableIRQ(I2C_SCL_EXTI_IRQN);
}

void IIC_GPIO_Config(void)
{
    GPIO_InitTypeDef I2C_GPIO_InitConfig = {0};

    __HAL_RCC_I2C_CLK_ENABLE();

    I2C_GPIO_InitConfig.Pin = I2C_SCL;
    I2C_GPIO_InitConfig.Mode = GPIO_MODE_AF_OD;
    I2C_GPIO_InitConfig.Pull = GPIO_NOPULL;
    I2C_GPIO_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    I2C_GPIO_InitConfig.Alternate = GPIO_AF6_I2C1;
    HAL_GPIO_Init(I2C_GPIO, &I2C_GPIO_InitConfig);

    I2C_GPIO_InitConfig.Pin = I2C_SDA;
    I2C_GPIO_InitConfig.Mode = GPIO_MODE_AF_OD;
    I2C_GPIO_InitConfig.Pull = GPIO_NOPULL;
    I2C_GPIO_InitConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    I2C_GPIO_InitConfig.Alternate = GPIO_AF6_I2C1;
    HAL_GPIO_Init(I2C_GPIO, &I2C_GPIO_InitConfig);

    NVIC_SetPriority(I2C_IRQN, 0);
    NVIC_EnableIRQ(I2C_IRQN);
}

void IIC_DISENABLE(void)
{
    HAL_I2C_DeInit(&IIC_H);
    __HAL_RCC_I2C_CLK_DISABLE();
}

void IIC_GPIO_Idle_Config(void)
{
    GPIO_InitTypeDef I2C_Idle_GPIO_InitConfig = {0};
    I2C_Idle_GPIO_InitConfig.Pin = I2C_SCL;
    I2C_Idle_GPIO_InitConfig.Mode = GPIO_MODE_IT_FALLING;
    I2C_Idle_GPIO_InitConfig.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(I2C_GPIO, &I2C_Idle_GPIO_InitConfig);

    I2C_Idle_GPIO_InitConfig.Pin = I2C_SDA;
    I2C_Idle_GPIO_InitConfig.Mode = GPIO_MODE_ANALOG; 
    I2C_Idle_GPIO_InitConfig.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(I2C_GPIO, &I2C_Idle_GPIO_InitConfig);

    NVIC_SetPriority(I2C_SCL_EXTI_IRQN, 0);
    NVIC_EnableIRQ(I2C_SCL_EXTI_IRQN);
}

void I2C_Slave_Handler(void)
{
    if(IIC_Restart == 1) //如果I2C异常需要重新初始化
    {
        IIC_Restart = 0;
        SET_BIT(IIC_H.Instance->CR1, I2C_CR1_SWRST);
        HAL_Delay(10);
        HAL_I2C_DeInit(&IIC_H);
		IIC_Config();
    }
}

/************************************************************************
 * Callback Function
 * Rewrite Function Content
 */
// 错误回调 主机未ACK从机时会触发
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        if (I2C_Noack) // 说明发送并由NACK结束 这是正常的
        {
            I2C_Noack = 0; // 清除异常
        }
        else // 意外错误
        {
            IIC_Restart = 1; // 设置I2C初始化标志位
        }
    }
}

// 从机监听完成回调
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        HAL_I2C_EnableListen_IT(&IIC_H); //State change LISTEN 
    }
}

// 发送数据完成回调
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        
        if (iic_slave[reg_adr].per == OR && iic_slave[reg_adr + data_count+2    ].per == OR)
        {
            if (I2C_state == STATE_READ)
            {
                /* code */
			    data_count++;
                HAL_I2C_Slave_Seq_Transmit_IT(&IIC_H, (uint8_t *)iic_slave[reg_adr + data_count].IIC_data, 1, I2C_FIRST_AND_LAST_FRAME);
                
            }
        // HAL_I2C_EnableListen_IT(&IIC_H); //调试用
        }
        else if (iic_slave[reg_adr].per == OW ||iic_slave[reg_adr + data_count].per == OW)
        {
            /* code */
            IIC_Restart = 1;
        }
    }
}

// 接收数据完成回调
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        if (iic_slave[reg_adr].per == OW)
        {
            if(I2C_state == STATE_ADDRESS)
            {
             I2C_state = STATE_WRITE; //地址匹配成功后第一次接收为当前寄存器数据
             data_offset = 0; 
             // HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, &slave_data[reg_adr], 1, I2C_FIRST_AND_LAST_FRAME); 
            }
            else if(I2C_state == STATE_WRITE)
            {
                data_offset ++;
            }
            HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, iic_slave[reg_adr + data_offset].IIC_data, 1, I2C_FIRST_AND_LAST_FRAME);
            IIC_Restart = 0;
        // I2C_state = STATE_IDLE; 
        }
        if (iic_slave[reg_adr].per == OR)
        {
            // IIC_Restart = 1;
        }
    }
}

// 地址匹配回调函数
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    if (hi2c->Instance == I2C1)
    {
        if (TransferDirection == I2C_DIRECTION_TRANSMIT) //发送
        {
            HAL_I2C_Slave_Seq_Transmit_IT(&IIC_H, &reg_adr, 1, I2C_FIRST_AND_LAST_FRAME);   //发送地址
            I2C_state = STATE_READ;
        }
        else if(TransferDirection == I2C_DIRECTION_RECEIVE)//接收
        {
            //换向
            data_count = 0;
            HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, &reg_adr, 1, I2C_FIRST_AND_LAST_FRAME);    //接收地址
            I2C_state = STATE_ADDRESS;
        }
    }
}


#endif
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
