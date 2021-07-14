////////////////////////////////////////////////////////////////////////////////
/// main�ļ�
/// ��������ϵͳ���豸������ʼ��������Ĵ��� 
/// @file    app.c 
/// @author  Lqc 
/// @date    2021-05-15
/// @version stm32_os
////////////////////////////////////////////////////////////////////////////////

// ������ͷ�ļ�
#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "comm_types.h"
#include "device_term.h"
#include "sysclk.h"

int main (void)
{
  
  HAL_Init();                    	//��ʼ��HAL�� 
  Stm32_Clock_Init();        //��ʼ��ʱ��
  delay_init();
  


  task_term();        
  
}




