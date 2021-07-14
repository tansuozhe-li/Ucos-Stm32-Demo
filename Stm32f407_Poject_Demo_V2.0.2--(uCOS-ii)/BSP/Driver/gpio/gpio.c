//-------------------------------------------------------------------------*
// 文件名: gpio.c                                                          *
// 说  明: gpio驱动程序文件                                                *
//-------------------------------------------------------------------------*

#include "gpio.h"

/*******************************************************************************
函数名称：drv_gpio_open
函数功能：配置相应引脚为GPIO功能,并配置GPIO的输入输出模式
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:指定的GPIO端口的具体某一位
          IO_Mode:GPIO口的输入输出模式
          data:若GPIO口配置成输出模式，则data=1表示port端口的bit引脚置高电平；
               data=0表示port端口的bit引脚置低电平。
               若GPIO口配置成输入模式，则data=1表示port端口的bit引脚内部上拉
               电阻使能；data=0表示port端口的bit引脚内部下拉电阻使能,data=2表示
               port端口的bit无上下拉。
出口参数：无
*******************************************************************************/
void drv_gpio_open(uint32_t port, int bit, GPIO_MODEL IO_Mode, u_int8_t data)
{
  
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    
    switch(port)                             // 使能相关GPIO时钟 
    {
        case PORTA:
            __HAL_RCC_GPIOA_CLK_ENABLE();
             break;
      
        case PORTB:
             __HAL_RCC_GPIOB_CLK_ENABLE();
             break;
      
        case PORTC:
           __HAL_RCC_GPIOC_CLK_ENABLE();
             break;
             
        case PORTD:
            __HAL_RCC_GPIOD_CLK_ENABLE();
             break;
             
        case PORTE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
             break;
        case PORTF:
            __HAL_RCC_GPIOF_CLK_ENABLE();
             break;
        case PORTG:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case PORTH:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        case PORTI:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
             
        default:
             break;
    }  
    ;
    GPIO_InitStruct.Pin = (uint16_t) bit;
    GPIO_InitStruct.Mode = IO_Mode;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
#if 1
    
    if(IO_Mode == INPUT)
    {
        if(1 == data)//上拉
        {
           GPIO_InitStruct.Pull = GPIO_PULLUP;
        }
        else if(0 == data)//下拉
        {
           GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        }
        else if(2 == data)//无/*!< No Pull-up or Pull-down activation  */
        {
           GPIO_InitStruct.Pull = GPIO_NOPULL;
        }
        HAL_GPIO_Init(GPIO_port_type, &GPIO_InitStruct);
    }
    else if(IO_Mode == OUTPUT)
    {        
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIO_port_type, &GPIO_InitStruct);
        if(1 == data)
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_SET);         //相应端口引脚置1
        }
        else
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_RESET);         //相应端口引脚清0
        }
    }
    else
    {
      GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIO_port_type, &GPIO_InitStruct);
        if(1 == data)
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_SET);         //相应端口引脚置1
        }
        else
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_RESET);         //相应端口引脚清0
        }
    }
    
#endif
}


/********************************************************************************
函数名称：drv_gpio_setbit
函数功能：设置指定端口的某一位为高电平
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:指定的GPIO端口的具体某一位
出口参数：无
********************************************************************************/

void drv_gpio_setbit(uint32_t port, int bit)
{  
   GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
   HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_SET);
}

/********************************************************************************
函数名称：drv_gpio_clrbit
函数功能：设置指定端口的某一位为低电平
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:指定的GPIO端口的具体某一位
出口参数：无
********************************************************************************/

void drv_gpio_clrbit(uint32_t port, int bit)
{ 
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_RESET);
}


/********************************************************************************
函数名称：drv_gpio_togglebit
函数功能：将指定端口某一位电平值取反
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:指定的GPIO端口的具体某一位
出口参数：无
*************************************************************/

void drv_gpio_togglebit(uint32_t port, int bit)
{   
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    HAL_GPIO_TogglePin(GPIO_port_type,bit);
}


/********************************************************************************
函数名称：drv_gpio_getbit
函数功能：读取指定引脚的电平值
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:指定的GPIO端口的具体某一位
出口参数：返回指定引脚的电平值
********************************************************************************/

u_int32_t drv_gpio_getbit(uint32_t port, int bit)
{
    u_int32_t In_value = 0;  
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    if(HAL_GPIO_ReadPin(GPIO_port_type,bit))
    {
        In_value = 1;  
    }
    else
    {
        In_value = 0;
    }

    return In_value;    
}


/********************************************************************************
函数名称：drv_gpio_setportbits
函数功能：向指定端口输出指定数据
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          outdata:指定的数据值
出口参数：无
********************************************************************************/

void drv_gpio_setportbits(uint32_t port, int outdata)
{   
    //GPIO_PDOR_REG(port) = outdata;
}


/********************************************************************************
函数名称：drv_gpio_reversebit
函数功能：改变指定引脚的状态
入口参数：port:指定的GPIO端口,如PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:指定的引脚
出口参数：无
********************************************************************************/

void drv_gpio_reversebit(uint32_t port, int bit)
{  
   // GPIO_PDOR_REG(port) ^= (1 << bit);
}












