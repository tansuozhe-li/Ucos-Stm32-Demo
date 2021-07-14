/**
  ******************************************************************************
  * File Name          : sysclk.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "cpu.h"
//#include  <bsp.h>
//#include "bsp.h"
#include "sysclk.h"

    
/*****************************************************************************
**********************���´���ο����ϣ�����ѧϰ�ο�**************************
*****************************************************************************/
/****************************************************************************
* ��    ��: void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
* ��    �ܣ�ʱ��ϵͳ���ú���
* ��ڲ�����Fvco:VCOƵ��
            SYSCLK:ϵͳʱ��Ƶ��
            Fusb:USB,SDIO,RNG�ȵ�ʱ��Ƶ��
            Fs:PLL����ʱ��Ƶ��,������HSI,HSE��. 
            plln:��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:64~432.
            pllm:��PLL����ƵPLL��Ƶϵ��(PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
            pllp:ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,4,6,8.(������4��ֵ!)
            pllq:USB/SDIO/������������ȵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~15.
* ���ز�������
* ˵    ����Fvco=Fs*(plln/pllm);
            SYSCLK=Fvco/pllp=Fs*(plln/(pllm*pllp));
            Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));�ⲿ����Ϊ8M��ʱ��,�Ƽ�ֵ:plln=336,pllm=8,pllp=2,pllq=7.
            �õ�:Fvco=8*(336/8)=336Mhz
            SYSCLK=336/2=168Mhz
            Fusb=336/7=48Mhz
****************************************************************************/
void Stm32_Clock_Init(void)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure; 
    RCC_ClkInitTypeDef RCC_ClkInitStructure;
    
    __HAL_RCC_PWR_CLK_ENABLE(); //ʹ��PWRʱ��
    
    //������������������õ�ѹ�������ѹ�����Ա�������δ�����Ƶ�ʹ���
    //ʱʹ�����빦��ʵ��ƽ�⡣
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);//���õ�ѹ�������ѹ����1
    
    RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    //ʱ��ԴΪHSE
    RCC_OscInitStructure.HSEState=RCC_HSE_ON;                      //��HSE
    RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;//��PLL
    RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;//PLLʱ��Դѡ��HSE
    RCC_OscInitStructure.PLL.PLLM=8; //��PLL����ƵPLL��Ƶϵ��(PLL֮ǰ�ķ�Ƶ),ȡֵ��Χ:2~63.
    RCC_OscInitStructure.PLL.PLLN=336; //��PLL��Ƶϵ��(PLL��Ƶ),ȡֵ��Χ:64~432.  
    RCC_OscInitStructure.PLL.PLLP=2; //ϵͳʱ�ӵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2,4,6,8.(������4��ֵ!)
    RCC_OscInitStructure.PLL.PLLQ=7; //USB/SDIO/������������ȵ���PLL��Ƶϵ��(PLL֮��ķ�Ƶ),ȡֵ��Χ:2~15.
    ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);//��ʼ��
	
    if(ret!=HAL_OK) while(1);
    
    //ѡ��PLL��Ϊϵͳʱ��Դ��������HCLK,PCLK1��PCLK2
    RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;//����ϵͳʱ��ʱ��ԴΪPLL
    RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;//AHB��Ƶϵ��Ϊ1
    RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV4; //APB1��Ƶϵ��Ϊ4
    RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV2; //APB2��Ƶϵ��Ϊ2
    ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_5);//ͬʱ����FLASH��ʱ����Ϊ5WS��Ҳ����6��CPU���ڡ�
		
    if(ret!=HAL_OK) while(1);

	 //STM32F405x/407x/415x/417x Z�汾������֧��Ԥȡ����
	if (HAL_GetREVID() == 0x1001)
	{
		__HAL_FLASH_PREFETCH_BUFFER_ENABLE();  //ʹ��flashԤȡ
	}
}

//����ϵͳ�δ�ʱ����д����ʱ����

static u_int8_t  fac_us=0; //us��ʱ������			   

/****************************************************************************
* ��    ��: delay_init()
* ��    �ܣ���ʱ������ʼ��
* ��ڲ�������
* ���ز�������
* ˵    ����
****************************************************************************/
void delay_init()
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
  fac_us=SYSCLK/8;   
}								    

/****************************************************************************
* ��    ��: void delay_us(u32 nus)
* ��    �ܣ���ʱnus
* ��ڲ�����Ҫ��ʱ��΢����
* ���ز�������
* ˵    ����nus��ֵ,��Ҫ����798915us
****************************************************************************/
void delay_us(u_int32_t nus)
{		
	u_int32_t midtime;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ���� 
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}

/****************************************************************************
* ��    ��: void delay_ms(u16 nms)
* ��    �ܣ���ʱnms
* ��ڲ�����Ҫ��ʱ�ĺ�����
* ���ز�������
* ˵    ���� 
****************************************************************************/
void delay_ms(u_int16_t nms)
{
	u_int32_t i;
	for(i=0;i<nms;i++) 
  {
    delay_us(1000);
  }
} 

	
