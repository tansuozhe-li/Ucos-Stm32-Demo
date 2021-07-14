//-------------------------------------------------------------------------*
// �ļ���: gpio.h                                                          *
// ˵  ��: gpio����ͷ�ļ�                                                  *
//-------------------------------------------------------------------------*

#ifndef __GPIO_H__
#define __GPIO_H__

#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "comm_types.h"
//#define   GPIO_PIN_MASK            0x1Fu
//#define   GPIO_PIN(x)              (((1)<<(x & GPIO_PIN_MASK)))


/*  �˿ڻ���ַ�Ķ���   */
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


/* ����Ӧ���Ų�����ΪGPIO����,����GPIO����Ϊ��������ģʽ  */
void drv_gpio_open(uint32_t port, int bit, GPIO_MODEL IO_Mode, u_int8_t data);

/* ����ָ���˿ڵ�ĳһλΪ�ߵ�ƽ */
void drv_gpio_setbit(uint32_t port, int bit);

/* �趨ָ���˿ڵ�ĳһλΪ�͵�ƽ */
void drv_gpio_clrbit(uint32_t port, int bit);

/* ��ָ���˿�ĳһλ��ƽֵȡ��   */
void drv_gpio_togglebit(uint32_t port, int bit);

/* ��ȡָ�����ŵĵ�ƽֵ         */
u_int32_t drv_gpio_getbit(uint32_t port, int bit);

/* ��ָ���˿����ָ������       */
void drv_gpio_setportbits(uint32_t port, int outdata);

/* �ı�ָ�����ŵ�״̬           */
void drv_gpio_reverseit(uint32_t port, int bit);

#endif 



