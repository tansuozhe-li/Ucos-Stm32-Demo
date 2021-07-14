//-------------------------------------------------------------------------*
// �ļ���: gpio.c                                                          *
// ˵  ��: gpio���������ļ�                                                *
//-------------------------------------------------------------------------*

#include "gpio.h"

/*******************************************************************************
�������ƣ�drv_gpio_open
�������ܣ�������Ӧ����ΪGPIO����,������GPIO���������ģʽ
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:ָ����GPIO�˿ڵľ���ĳһλ
          IO_Mode:GPIO�ڵ��������ģʽ
          data:��GPIO�����ó����ģʽ����data=1��ʾport�˿ڵ�bit�����øߵ�ƽ��
               data=0��ʾport�˿ڵ�bit�����õ͵�ƽ��
               ��GPIO�����ó�����ģʽ����data=1��ʾport�˿ڵ�bit�����ڲ�����
               ����ʹ�ܣ�data=0��ʾport�˿ڵ�bit�����ڲ���������ʹ��,data=2��ʾ
               port�˿ڵ�bit����������
���ڲ�������
*******************************************************************************/
void drv_gpio_open(uint32_t port, int bit, GPIO_MODEL IO_Mode, u_int8_t data)
{
  
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    
    switch(port)                             // ʹ�����GPIOʱ�� 
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
        if(1 == data)//����
        {
           GPIO_InitStruct.Pull = GPIO_PULLUP;
        }
        else if(0 == data)//����
        {
           GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        }
        else if(2 == data)//��/*!< No Pull-up or Pull-down activation  */
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
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_SET);         //��Ӧ�˿�������1
        }
        else
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_RESET);         //��Ӧ�˿�������0
        }
    }
    else
    {
      GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIO_port_type, &GPIO_InitStruct);
        if(1 == data)
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_SET);         //��Ӧ�˿�������1
        }
        else
        {
          HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_RESET);         //��Ӧ�˿�������0
        }
    }
    
#endif
}


/********************************************************************************
�������ƣ�drv_gpio_setbit
�������ܣ�����ָ���˿ڵ�ĳһλΪ�ߵ�ƽ
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:ָ����GPIO�˿ڵľ���ĳһλ
���ڲ�������
********************************************************************************/

void drv_gpio_setbit(uint32_t port, int bit)
{  
   GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
   HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_SET);
}

/********************************************************************************
�������ƣ�drv_gpio_clrbit
�������ܣ�����ָ���˿ڵ�ĳһλΪ�͵�ƽ
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:ָ����GPIO�˿ڵľ���ĳһλ
���ڲ�������
********************************************************************************/

void drv_gpio_clrbit(uint32_t port, int bit)
{ 
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    HAL_GPIO_WritePin(GPIO_port_type, (uint16_t) bit, GPIO_PIN_RESET);
}


/********************************************************************************
�������ƣ�drv_gpio_togglebit
�������ܣ���ָ���˿�ĳһλ��ƽֵȡ��
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:ָ����GPIO�˿ڵľ���ĳһλ
���ڲ�������
*************************************************************/

void drv_gpio_togglebit(uint32_t port, int bit)
{   
    GPIO_TypeDef* GPIO_port_type = ((GPIO_TypeDef *) port);
    HAL_GPIO_TogglePin(GPIO_port_type,bit);
}


/********************************************************************************
�������ƣ�drv_gpio_getbit
�������ܣ���ȡָ�����ŵĵ�ƽֵ
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:ָ����GPIO�˿ڵľ���ĳһλ
���ڲ���������ָ�����ŵĵ�ƽֵ
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
�������ƣ�drv_gpio_setportbits
�������ܣ���ָ���˿����ָ������
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          outdata:ָ��������ֵ
���ڲ�������
********************************************************************************/

void drv_gpio_setportbits(uint32_t port, int outdata)
{   
    //GPIO_PDOR_REG(port) = outdata;
}


/********************************************************************************
�������ƣ�drv_gpio_reversebit
�������ܣ��ı�ָ�����ŵ�״̬
��ڲ�����port:ָ����GPIO�˿�,��PORTA,PORTB,PORTC,PORTC,PORTD,PORTE
          bit:ָ��������
���ڲ�������
********************************************************************************/

void drv_gpio_reversebit(uint32_t port, int bit)
{  
   // GPIO_PDOR_REG(port) ^= (1 << bit);
}












