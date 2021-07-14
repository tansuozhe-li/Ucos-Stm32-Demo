#ifndef  _DEVICE_TERM_
#define  _DEVICE_TERM_

#include "gpio.h"

#define led0_open  drv_gpio_open(PORTG,GPIO_PIN_13,OUTPUT,1)
#define led1_open  drv_gpio_open(PORTG,GPIO_PIN_14,OUTPUT,1)
        
#define led0_on    drv_gpio_clrbit(PORTG,GPIO_PIN_13)
#define led1_on    drv_gpio_clrbit(PORTG,GPIO_PIN_14)

#define led0_off   drv_gpio_setbit(PORTG,GPIO_PIN_13)
#define led1_off   drv_gpio_setbit(PORTG,GPIO_PIN_14)

#define been_open  drv_gpio_open(PORTG,GPIO_PIN_7,OUTPUT,1)
#define been_on    drv_gpio_setbit(PORTG,GPIO_PIN_7)
#define been_off    drv_gpio_clrbit(PORTG,GPIO_PIN_7)



void init_term_moudle();

#endif