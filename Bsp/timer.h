/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： timer.h
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： 定时器头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _TIMER_H
#define _TIMER_H


/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f4xx.h"


/* 宏定义 --------------------------------------------------------------------*/
#define TIM4_COUNTER_CLOCK        42000000                 //计数时钟(相当于1秒钟计数42M次个脉冲)
                                                           //预分频值
#define TIM4_PRESCALER_VALUE      (SystemCoreClock/2/TIM4_COUNTER_CLOCK - 1)
#define TIM4_PERIOD_TIMING        (42 - 1)                 //定时周期(计数满42个脉冲才算一个周期, 即1秒冲计数1M次个周期)


#define TIM2_COUNTER_CLOCK        42000000                 //计数时钟(42M次/秒)
                                                           //预分频值
#define TIM2_PRESCALER_VALUE      (SystemCoreClock/2/TIM2_COUNTER_CLOCK - 1)

/* 函数申明 ------------------------------------------------------------------*/
void TIMER_Initializes(void);
void TIMER1_Initializes(void);

void TIMDelay_Nus(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);

void TIMER_IC_Initializes(void);

void TIMER_PWM_GPIO_Configuration(void);
void TIM2_CH2_PWM(uint32_t Freq, uint16_t Dutycycle);


#endif /* _TIMER_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
