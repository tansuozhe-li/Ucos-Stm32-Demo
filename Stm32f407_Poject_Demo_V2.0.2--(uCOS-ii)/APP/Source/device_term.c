////////////////////////////////////////////////////////////////////////////////
/// device_term 文件
/// 终端交互任务创建，用以测试传感器设备 
/// @file    device_term.c 
/// @author  Lqc 
/// @date    2021-05-18
/// @version stm32_os
////////////////////////////////////////////////////////////////////////////////
#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "includes.h"
#include "device_term.h"
#include "comm_types.h"


void task_term()
{
     been_open;
     led0_open;
     led1_open;
  while(1)
  {
    OSTimeDlyHMSM(0u, 0u, 1u, 0u);
     been_on;
     led0_on;
     led0_on;
     OSTimeDlyHMSM(0u, 0u, 1u, 0u);
     led1_off;
     led1_off;
     been_off;
     OSTimeDlyHMSM(0u, 0u, 10u,0u);
  }
}

/// 创建终端交互任务 
///
/// @param  none   
/// @param  none
/// @return none 
/// @note   修改日志
///         Lqc与2021-05-22创建
static OS_STK task_term_stk[TASK_TERM_STK_SIZE];
static void task_create_term (void)
{ 
   CPU_INT08U  task_err;   
   CPU_INT08U  name_err;
   
   task_err = OSTaskCreateExt((void (*)(void *)) task_term,           
		   (void           *) 0,
		   (OS_STK         *)&task_term_stk[TASK_TERM_STK_SIZE - 1],
		   (INT8U           ) TASK_TERM_PRIO,                   
		   (INT16U          ) TASK_TERM_PRIO,
		   (OS_STK         *)&task_term_stk[0],
		   (INT32U          ) TASK_TERM_STK_SIZE,
		   (void           *) 0,
		   (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));     
    #if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(TASK_TERM_PRIO, "task_term", &name_err);
    #endif
       
//    if ((task_err == OS_ERR_NONE) && (name_err == OS_ERR_NONE)) {
//        pdebug(DEBUG_LEVEL_INFO,"create task_term success...\n\r");
//	} else { 
//        pdebug(DEBUG_LEVEL_FATAL,"create task_term failed...\n\r");
//	}
}

/// 终端交互模块初始化 
///
/// 创建任务
/// @param  none   
/// @param  none
/// @return none   
/// @note   修改日志 
///         Lqc与2021-05-18创建
void init_term_moudle()
{
  //创建串口终端交互任务
  task_create_term();
  
}