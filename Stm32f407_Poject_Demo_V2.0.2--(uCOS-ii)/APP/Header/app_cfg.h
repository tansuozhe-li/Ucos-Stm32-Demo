/*
********************************************************************************
*                          APPLICATION CONFIGURATION
*
*                         ST Microelectronics STM32
*                                  on the
*
*                               STM3240G-EVAL
*                             Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : DC
********************************************************************************
*/
#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT

/*******************************************************************************
                          MODULE ENABLE / DISABLE
*******************************************************************************/

#define  APP_CFG_SERIAL_EN                      DEF_ENABLED


/*******************************************************************************
                              TASK PRIORITIES
*******************************************************************************/

#define  TASK_START_PRIO                3u
#define  TASK_TERM_PRIO                 4u
#define  TASK_FEEDDOG_PRIO              (OS_LOWEST_PRIO - 3u)
#define  OS_TASK_TMR_PRIO               (OS_LOWEST_PRIO - 2u)



/*******************************************************************************
                                TASK STACK SIZES
                   Size of the task stacks (# of OS_STK entries)
*******************************************************************************/

#define  TASK_START_STK_SIZE             1000u
#define  TASK_TERM_STK_SIZE              400u
#define  TASK_FEEDDOG_STK_SIZE           200u 



#endif


