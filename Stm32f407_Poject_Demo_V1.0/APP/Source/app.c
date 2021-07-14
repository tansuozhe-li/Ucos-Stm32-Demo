////////////////////////////////////////////////////////////////////////////////
/// main文件
/// 包含操作系统、设备驱动初始化及任务的创建 
/// @file    app.c 
/// @author  Lqc 
/// @date    2021-05-15
/// @version stm32_os
////////////////////////////////////////////////////////////////////////////////

// 包含的头文件
#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "comm_types.h"
#include "device_term.h"
#include "sysclk.h"

int main (void)
{
  
  HAL_Init();                    	//初始化HAL库 
  Stm32_Clock_Init();        //初始化时钟
  delay_init();
  


  task_term();        
  
}




