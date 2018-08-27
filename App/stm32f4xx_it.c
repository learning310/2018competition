/**
  ******************************************************************************
  * @file    CAN/CAN_Networking/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    22-April-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "usart.h"
#include "global_variable.h"


/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s).                         */
/******************************************************************************/
/************************************************
�������� �� USART1_IRQHandler
��    �� �� USART1�ж�
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART1_IRQHandler(void)
{
  if((USART1->SR & USART_FLAG_RXNE) == USART_FLAG_RXNE)
  {
    USART1_SendByte((uint8_t)(USART1->DR));      //���ͽ��յ����ַ�����
  }
}

/************************************************
�������� �� TIM5_IRQHandler
��    �� �� ��ʱ��5
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIM3_IRQHandler(void)
{
  static uint32_t capture_value0 = 0, capture_value2 = 0;
  static uint32_t capture_value1 = 0;

  static uint16_t flag_capture = 0;              //��־

  static uint32_t difference_value_period;       //���������ڲ�ֵ
  static uint32_t difference_value_dutycycle;    //������ռ�ձȲ�ֵ
	
  /* ͨ��1���������� - Ƶ�� */
  if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);     //����жϱ�־

    if(flag_capture == 0)
    {
      capture_value0 = (uint32_t)(TIM3->CCR1);   //������ֵ1
      flag_capture = 1;                          //�л���־λ
    }
    else if(flag_capture == 1)
    {
      flag_capture = 0;
      capture_value2 = (uint32_t)(TIM3->CCR1);   //������ֵ2

      /* ���㲶���ֵ��ռ�ձ� */
      if(capture_value2 > capture_value0)
      {
        difference_value_period = (capture_value2 - capture_value0);
        difference_value_dutycycle = capture_value1 - capture_value0;
      }
      else if(capture_value2 < capture_value0)
      {
        difference_value_period = ((0xFFFFFFFF - capture_value0) + capture_value2);
        if(capture_value0 <= capture_value1)
          difference_value_dutycycle = capture_value1 - capture_value0;
        else
          difference_value_dutycycle = (0xFFFFFFFF - capture_value0) + capture_value1;
      }
      else
      {
        difference_value_period = 0;
        difference_value_dutycycle = 0;
      }
		}
      /* ����Ƶ�� */
    Freq_InputCapture = (SystemCoreClock/2 / difference_value_period)*4;	
		DutyCycle_InputCapture = difference_value_dutycycle * 40000 /(difference_value_period);
  }

  /* ͨ��2�����½��� - ռ�ձ� */
  if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);     //����жϱ�־

    if(flag_capture == 1)
    {
      capture_value1 = (uint32_t)(TIM3->CCR2);   //������ֵ1
    }
  }
	
}

void TIM5_IRQHandler(void)
{
  static uint32_t capture_value0 = 0, capture_value2 = 0;
	
  static uint16_t flag_capture = 0;              //��־

  static uint32_t difference_value_period;       //���������ڲ�ֵ

  /* ͨ��3���������� - Ƶ�� */
  if(TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);     //����жϱ�־

    if(flag_capture == 0)
    {
      capture_value0 = (uint32_t)(TIM5->CCR4);   //������ֵ1
      flag_capture = 1;                          //�л���־λ
    }
    else if(flag_capture == 1)
    {
      flag_capture = 0;
      capture_value2 = (uint32_t)(TIM5->CCR4);   //������ֵ2

      /* ���㲶���ֵ��ռ�ձ� */
      if(capture_value2 > capture_value0)
      {
        difference_value_period = (capture_value2 - capture_value0);
      }
      else if(capture_value2 < capture_value0)
      {
        difference_value_period = ((0xFFFFFFFF - capture_value0) + capture_value2);
      }
      else
      {
        difference_value_period = 0;
      }

      /* ����Ƶ�� */
			Freq_InputCapture = (SystemCoreClock/2 / difference_value_period) + 1;
    }
  }
}

void EXTI0_IRQHandler()
{
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
      TIM_Cmd(TIM1, ENABLE); 
      EXTI_ClearITPendingBit(EXTI_Line0);         // ����жϱ�־
  }
}

void EXTI1_IRQHandler()
{
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
      Rise = TIM1->CNT;
      TIM1->CNT = 0;
      TIM_Cmd(TIM1, DISABLE);
      EXTI_ClearITPendingBit(EXTI_Line1);       // ����жϱ�־
  }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
