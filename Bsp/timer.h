/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� timer.h
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� ��ʱ��ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _TIMER_H
#define _TIMER_H


/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f4xx.h"


/* �궨�� --------------------------------------------------------------------*/
#define TIM4_COUNTER_CLOCK        42000000                 //����ʱ��(�൱��1���Ӽ���42M�θ�����)
                                                           //Ԥ��Ƶֵ
#define TIM4_PRESCALER_VALUE      (SystemCoreClock/2/TIM4_COUNTER_CLOCK - 1)
#define TIM4_PERIOD_TIMING        (42 - 1)                 //��ʱ����(������42���������һ������, ��1������1M�θ�����)


#define TIM2_COUNTER_CLOCK        42000000                 //����ʱ��(42M��/��)
                                                           //Ԥ��Ƶֵ
#define TIM2_PRESCALER_VALUE      (SystemCoreClock/2/TIM2_COUNTER_CLOCK - 1)

/* �������� ------------------------------------------------------------------*/
void TIMER_Initializes(void);
void TIMER1_Initializes(void);

void TIMDelay_Nus(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);

void TIMER_IC_Initializes(void);

void TIMER_PWM_GPIO_Configuration(void);
void TIM2_CH2_PWM(uint32_t Freq, uint16_t Dutycycle);


#endif /* _TIMER_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
