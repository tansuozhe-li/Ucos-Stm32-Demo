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
**********************以下代码参考网上，仅供学习参考**************************
*****************************************************************************/
/****************************************************************************
* 名    称: void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq)
* 功    能：时钟系统配置函数
* 入口参数：Fvco:VCO频率
            SYSCLK:系统时钟频率
            Fusb:USB,SDIO,RNG等的时钟频率
            Fs:PLL输入时钟频率,可以是HSI,HSE等. 
            plln:主PLL倍频系数(PLL倍频),取值范围:64~432.
            pllm:主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63.
            pllp:系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
            pllq:USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15.
* 返回参数：无
* 说    明：Fvco=Fs*(plln/pllm);
            SYSCLK=Fvco/pllp=Fs*(plln/(pllm*pllp));
            Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));外部晶振为8M的时候,推荐值:plln=336,pllm=8,pllp=2,pllq=7.
            得到:Fvco=8*(336/8)=336Mhz
            SYSCLK=336/2=168Mhz
            Fusb=336/7=48Mhz
****************************************************************************/
void Stm32_Clock_Init(void)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure; 
    RCC_ClkInitTypeDef RCC_ClkInitStructure;
    
    __HAL_RCC_PWR_CLK_ENABLE(); //使能PWR时钟
    
    //下面这个设置用来设置调压器输出电压级别，以便在器件未以最大频率工作
    //时使性能与功耗实现平衡。
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);//设置调压器输出电压级别1
    
    RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    //时钟源为HSE
    RCC_OscInitStructure.HSEState=RCC_HSE_ON;                      //打开HSE
    RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;//打开PLL
    RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;//PLL时钟源选择HSE
    RCC_OscInitStructure.PLL.PLLM=8; //主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63.
    RCC_OscInitStructure.PLL.PLLN=336; //主PLL倍频系数(PLL倍频),取值范围:64~432.  
    RCC_OscInitStructure.PLL.PLLP=2; //系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
    RCC_OscInitStructure.PLL.PLLQ=7; //USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15.
    ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);//初始化
	
    if(ret!=HAL_OK) while(1);
    
    //选中PLL作为系统时钟源并且配置HCLK,PCLK1和PCLK2
    RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;//设置系统时钟时钟源为PLL
    RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;//AHB分频系数为1
    RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV4; //APB1分频系数为4
    RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV2; //APB2分频系数为2
    ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_5);//同时设置FLASH延时周期为5WS，也就是6个CPU周期。
		
    if(ret!=HAL_OK) while(1);

	 //STM32F405x/407x/415x/417x Z版本的器件支持预取功能
	if (HAL_GetREVID() == 0x1001)
	{
		__HAL_FLASH_PREFETCH_BUFFER_ENABLE();  //使能flash预取
	}
}

//利用系统滴答定时，编写的延时函数

static u_int8_t  fac_us=0; //us延时倍乘数			   

/****************************************************************************
* 名    称: delay_init()
* 功    能：延时函数初始化
* 入口参数：无
* 返回参数：无
* 说    明：
****************************************************************************/
void delay_init()
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
  fac_us=SYSCLK/8;   
}								    

/****************************************************************************
* 名    称: void delay_us(u32 nus)
* 功    能：延时nus
* 入口参数：要延时的微妙数
* 返回参数：无
* 说    明：nus的值,不要大于798915us
****************************************************************************/
void delay_us(u_int32_t nus)
{		
	u_int32_t midtime;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数 
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}

/****************************************************************************
* 名    称: void delay_ms(u16 nms)
* 功    能：延时nms
* 入口参数：要延时的毫妙数
* 返回参数：无
* 说    明： 
****************************************************************************/
void delay_ms(u_int16_t nms)
{
	u_int32_t i;
	for(i=0;i<nms;i++) 
  {
    delay_us(1000);
  }
} 

	
