#ifndef __sysclk_H
#define __sysclk_H

#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "comm_types.h"

#define SYSCLK 168    //œµÕ≥ ±÷”

void Stm32_Clock_Init(void);
void delay_init(void);
void delay_ms(u_int16_t nms);
void delay_us(u_int32_t nus);

#endif


