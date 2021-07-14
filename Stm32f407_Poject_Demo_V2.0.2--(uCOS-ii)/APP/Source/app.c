////////////////////////////////////////////////////////////////////////////////
/// @file    app.c �ļ�
/// @brief   ��ʼ���񴴽���ģ���ʼ�� 
/// 
/// @author  Lqc 
/// @date    2021-05-22
/// @version v2.0 2021/05/22   uCOSii����ϵͳ��ֲ�汾
////////////////////////////////////////////////////////////////////////////////
/**********************************������ͷ�ļ�*********************************/
#include <stm32f4xx_hal.h>
#include "includes.h"
#include "device_term.h"


///@brief     AppTaskStart
///
///@brief    ��ʼ����,��ʼ����������������
///
///@return   0 - �ɹ���-1 - ʧ��
///@date     2021-05-22
static  void  AppTaskStart (void *p_arg)
{

    BSP_Init();                      /* Initialize BSP functions*/
    CPU_Init();                      /* Initialize the uC/CPU services*/
    BSP_Tick_Init();                 /* Initialize the uC/CPU tick*/
    
#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                    /* Determine CPU capacity*/
#endif

   init_term_moudle();
    
    while (DEF_TRUE) {             
       OSTaskDel(OS_PRIO_SELF);
    }
}

///@brief     main����
///
///@brief    ������ʼ����
///
///@return   0 - �ɹ���-1 - ʧ��
///@date     2021-05-22
static OS_STK AppTaskStartStk[TASK_START_STK_SIZE];
int main(void)
{

    CPU_INT08U  name_err;
    
    HAL_Init();                               //��ʼ��HAL��                                                                         
    Mem_Init();                               //��ʼ���ڴ����ģ��
    Math_Init();                              //��ʼ����ѧģ��
    BSP_IntDisAll();                          //���������ж�
    OSInit();                                 //Init uC/OS-II

    OSTaskCreateExt((void (*)(void *)) AppTaskStart,           
		   (void           *) 0,
		   (OS_STK         *)&AppTaskStartStk[TASK_START_STK_SIZE - 1],
		   (INT8U           ) TASK_START_PRIO,                   
		   (INT16U          ) TASK_START_PRIO,
		   (OS_STK         *)&AppTaskStartStk[0],
		   (INT32U          ) TASK_START_STK_SIZE,
		   (void           *) 0,
		   (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR)); 

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet(TASK_START_PRIO,(INT8U *)"Start Task",&name_err);
#endif

    OSStart();         /* Start multitasking (i.e. give control to uC/OS-II).  */
    
}


