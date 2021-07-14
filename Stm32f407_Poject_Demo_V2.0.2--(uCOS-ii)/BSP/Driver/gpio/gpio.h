//-------------------------------------------------------------------------*
// 文件名: gpio.h                                                          *
// 说  明: gpio驱动头文件                                                  *
//-------------------------------------------------------------------------*

#ifndef __GPIO_H__
#define __GPIO_H__

#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "comm_types.h"
//#define   GPIO_PIN_MASK            0x1Fu
//#define   GPIO_PIN(x)              (((1)<<(x & GPIO_PIN_MASK)))


/*  端口基地址的定义   */
#define   PORTA   GPIOA_BASE
#define   PORTB   GPIOB_BASE
#define   PORTC   GPIOC_BASE
#define   PORTD   GPIOD_BASE
#define   PORTE   GPIOE_BASE
#define   PORTF   GPIOF_BASE
#define   PORTG   GPIOG_BASE
#define   PORTH   GPIOH_BASE
#define   PORTI   GPIOI_BASE

typedef enum
{
    INPUT = 0x00000000u,
	
    OUTPUT = 0x00000001u,
    
    OUTPUT_OD = 0x00000011u,
    
    
}GPIO_MODEL;


/* 打开相应引脚并配置为GPIO功能,设置GPIO引脚为输入或输出模式  */
void drv_gpio_open(uint32_t port, int bit, GPIO_MODEL IO_Mode, u_int8_t data);

/* 设置指定端口的某一位为高电平 */
void drv_gpio_setbit(uint32_t port, int bit);

/* 设定指定端口的某一位为低电平 */
void drv_gpio_clrbit(uint32_t port, int bit);

/* 将指定端口某一位电平值取反   */
void drv_gpio_togglebit(uint32_t port, int bit);

/* 读取指定引脚的电平值         */
u_int32_t drv_gpio_getbit(uint32_t port, int bit);

/* 向指定端口输出指定数据       */
void drv_gpio_setportbits(uint32_t port, int outdata);

/* 改变指定引脚的状态           */
void drv_gpio_reverseit(uint32_t port, int bit);

#endif 



