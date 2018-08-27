/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� global_variable.h
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� ȫ�ֱ���ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _GLOBAL_VERIABLE_H
#define _GLOBAL_VERIABLE_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "global_define.h"
#define SIZE (50)

/* ȫ�ֱ��� ------------------------------------------------------------------*/
/* TIM��ʱ�� */
extern volatile uint32_t Freq_InputCapture;                //��������Ƶ��
extern volatile uint32_t DutyCycle_InputCapture;           //��������ռ�ձ�
extern volatile uint32_t Rise;                         // ����ʱ��

extern uint16_t data[SIZE];
extern uint32_t Max;

#endif /* _GLOBAL_VERIABLE_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
