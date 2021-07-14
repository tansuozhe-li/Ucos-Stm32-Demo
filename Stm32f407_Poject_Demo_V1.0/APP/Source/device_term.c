////////////////////////////////////////////////////////////////////////////////
/// device_term �ļ�
/// �ն˽������񴴽������Բ��Դ������豸 
/// @file    device_term.c 
/// @author  Lqc 
/// @date    2021-05-18
/// @version stm32_os
////////////////////////////////////////////////////////////////////////////////

#include "device_term.h"
#include  "comm_types.h"
#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "sysclk.h"

void task_term()
{
  while(1)
  {
    delay_ms(3000);
    been_open;
     led0_open;
     led1_open;
     delay_ms(3000);
     been_on;
     led0_on;
     led0_on;
delay_ms(3000);
     led1_off;
     led1_off;
      been_off;
      delay_ms(3000);
  }
  
  
}


///// �����ն˽������� 
/////
///// @param  none   
///// @param  none
///// @return none 
///// @note   �޸���־
/////         gkl��2017-05-26����
//static OS_STK task_term_stk[TASK_TERM_STK_SIZE];
//static void task_create_term (void)
//{ 
//   CPU_INT08U  task_err;   
//   CPU_INT08U  name_err;
//   
//   task_err = OSTaskCreateExt((void (*)(void *)) task_term,           
//		   (void           *) 0,
//		   (OS_STK         *)&task_term_stk[TASK_TERM_STK_SIZE - 1],
//		   (INT8U           ) TASK_TERM_PRIO,                   
//		   (INT16U          ) TASK_TERM_PRIO,
//		   (OS_STK         *)&task_term_stk[0],
//		   (INT32U          ) TASK_TERM_STK_SIZE,
//		   (void           *) 0,
//		   (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));     
//    #if (OS_TASK_NAME_EN > 0)
//    OSTaskNameSet(TASK_TERM_PRIO, "task_term", &name_err);
//    #endif
//       
////    if ((task_err == OS_ERR_NONE) && (name_err == OS_ERR_NONE)) {
////        pdebug(DEBUG_LEVEL_INFO,"create task_term success...\n\r");
////	} else { 
////        pdebug(DEBUG_LEVEL_FATAL,"create task_term failed...\n\r");
////	}
//}
//
//
//
///// �ն˽���ģ���ʼ�� 
/////
///// ��������
///// @param  none   
///// @param  none
///// @return none   
///// @note   �޸���־ 
/////         Lqc��2021-05-18����
//void init_term_moudle()
//{
//  //���������ն˽�������
//  task_create_term();
//  
//}