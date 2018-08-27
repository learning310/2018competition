/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� bsp.h
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� BSP�弶֧�ְ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f4xx.h"

/* �궨�� --------------------------------------------------------------------*/
#define PORT_LED                  GPIOA
#define PIN_LED                   GPIO_Pin_7

/* LED���� */
#define LED_ON                    GPIO_SetBits(PORT_LED, PIN_LED)
#define LED_OFF                   GPIO_ResetBits(PORT_LED, PIN_LED)
#define LED_TOGGLE                GPIO_ToggleBits(PORT_LED, PIN_LED)


/* �������� ------------------------------------------------------------------*/
void BSP_Initializes(void);
void RCC_Configuration(void);
void GPIO_Basic_Configuration(void);
void NVIC_Configuration(void);
void GPIO_EXTILineConfig(void);

#endif /* _BSP_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
