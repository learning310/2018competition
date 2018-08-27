/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： global_variable.h
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： 全局变量头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _GLOBAL_VERIABLE_H
#define _GLOBAL_VERIABLE_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "global_define.h"
#define SIZE (50)

/* 全局变量 ------------------------------------------------------------------*/
/* TIM定时器 */
extern volatile uint32_t Freq_InputCapture;                //输入脉冲频率
extern volatile uint32_t DutyCycle_InputCapture;           //输入脉冲占空比
extern volatile uint32_t Rise;                         // 上升时间

extern uint16_t data[SIZE];
extern uint32_t Max;

#endif /* _GLOBAL_VERIABLE_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
