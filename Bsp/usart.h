/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： usart.h
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： USART头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _USART_H
#define _USART_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>


/* 函数申明 ------------------------------------------------------------------*/
void USART_Initializes(void);
void USART1_SendByte(uint8_t Data);
void USART1_SendNByte(uint8_t *pData, uint16_t Length);
void USART1_SendString(uint8_t *String);


#endif /* _USART_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
