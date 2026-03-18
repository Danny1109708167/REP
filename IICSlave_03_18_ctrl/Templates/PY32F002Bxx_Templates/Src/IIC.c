/**
 ******************************************************************************
 * @file    IIC.c
 * @author  Dario Liu
 * @brief   IIC Config
 * @date    2026/03/12
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
uint8_t Reg_state = 0;
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
};

IIC_BUS iic_slave[] =
{
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
    {0x10, RW, Reg_8bit, (void *)&slave_data[16]},
    {0x11, RW, Reg_8bit, (void *)&slave_data[17]},
    {0x12, RW, Reg_8bit, (void *)&slave_data[18]},
    {0x13, RW, Reg_8bit, (void *)&slave_data[19]},
    {0x14, RW, Reg_8bit, (void *)&slave_data[20]},
    {0x15, RW, Reg_8bit, (void *)&slave_data[21]},
    {0x16, RW, Reg_8bit, (void *)&slave_data[22]},
    {0x17, RW, Reg_8bit, (void *)&slave_data[23]},
    {0x18, OW, Reg_8bit, (void *)&slave_data[24]},
    {0x19, OW, Reg_8bit, (void *)&slave_data[25]},
    {0x1A, OW, Reg_8bit, (void *)&slave_data[26]},
    {0x1B, OW, Reg_8bit, (void *)&slave_data[27]},
    {0x1C, OW, Reg_8bit, (void *)&slave_data[28]},
    {0x1D, OW, Reg_8bit, (void *)&slave_data[29]},
    {0x1E, OW, Reg_8bit, (void *)&slave_data[30]},
    {0x1F, OW, Reg_8bit, (void *)&slave_data[31]},

};

void IIC_Config(void)
{
    IIC_H.Instance = I2C;                                 /* I2C */
    IIC_H.Init.ClockSpeed = I2C_SPEEDCLOCK;               /* I2C communication speed */
    IIC_H.Init.DutyCycle = I2C_DUTYCYCLE_16_9;                 /* I2C duty cycle */
    IIC_H.Init.OwnAddress1 = I2C_ADDRESS;                 /* I2C address */
    IIC_H.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE; /* Prohibit broadcast calls */
    IIC_H.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;     /* Allow clock extension */
    HAL_I2C_Init(&IIC_H);

    HAL_I2C_EnableListen_IT(&IIC_H);
    // HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, &reg_adr, 1, I2C_FIRST_AND_LAST_FRAME);
    __HAL_I2C_ENABLE_IT(&IIC_H, I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR);
    
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
    SET_BIT(IIC_H.Instance->CR1, I2C_CR1_SWRST);
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
        IIC_Restart = 0;
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
uint8_t reg_all = 0;
// 发送数据完成回调
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        // if (reg_adr + data_offset >= 0x20)
        // {
        //     /* code */
        //     CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
        //     IIC_Restart = 1;
        // }
        if ((iic_slave[reg_adr].per == OW) || (iic_slave[reg_all-2].per == OW))
        {
            /* code */
            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
            IIC_Restart = 1;
        }
        if(iic_slave[reg_adr].per == OR || iic_slave[reg_adr].per == RW 
            || iic_slave[reg_adr + data_count].per == OR || iic_slave[reg_adr + data_count].per == RW)
        {
            if (I2C_state == STATE_READ)
            {
                /* code */
			    data_count++;
                reg_all = reg_adr+data_count;
                HAL_I2C_Slave_Seq_Transmit_IT(&IIC_H, &slave_data[reg_adr + data_count], 1, I2C_FIRST_AND_LAST_FRAME);
            }
        }
        
        // if (reg_adr+data_offset > sizeof(iic_slave->order_code))
        // {
        //     /* code */
        //     CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
        //     IIC_Restart = 1;
        // }
    }
}
// 接收数据完成回调
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        if (reg_adr + data_offset >= 0x20)
        {
            /* code */
            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
            IIC_Restart = 1;
        }
            if(I2C_state == STATE_ADDRESS )
        {
            I2C_state = STATE_WRITE; 
            data_offset = 0; 
            HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, &slave_data[reg_adr], 1, I2C_FIRST_AND_LAST_FRAME);
        }
        else if (iic_slave[reg_adr].per == OR || iic_slave[reg_adr + data_offset].per == OR)
        {
            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
            IIC_Restart = 1;
        }
        else if(I2C_state == STATE_WRITE && (iic_slave[reg_adr].per == OW || iic_slave[reg_adr].per == RW 
            || iic_slave[reg_adr + data_offset].per == OW || iic_slave[reg_adr + data_offset].per == RW))
        {
            data_offset ++;
            HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, iic_slave[reg_adr + data_offset].IIC_data, 1, I2C_FIRST_AND_LAST_FRAME);
            IIC_Restart = 0;
        }
        
        
        // I2C_state = STATE_IDLE; 
        // if (reg_adr+data_offset > sizeof(iic_slave->order_code))
        // {
        //     /* code */
        //     CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
        //     IIC_Restart = 1;
        // }
    }
}


// 地址匹配回调函数
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    if (hi2c->Instance == I2C1)
    {
        if (TransferDirection == I2C_DIRECTION_TRANSMIT) //发送
        {
            data_count = 0;
            HAL_I2C_Slave_Seq_Transmit_IT(&IIC_H, &slave_data[reg_adr], 1, I2C_FIRST_AND_LAST_FRAME);   //发送地址
            I2C_state = STATE_READ;
        }
        else if(TransferDirection == I2C_DIRECTION_RECEIVE)//接收
        {
            //换向
            HAL_I2C_Slave_Seq_Receive_IT(&IIC_H, &reg_adr, 1, I2C_FIRST_AND_LAST_FRAME);    //接收地址
            I2C_state = STATE_ADDRESS;
        }
    }
}

#endif
/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
