/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� bsp.c
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� BSP�弶֧�ְ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-07-12 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
�������� �� RCC_Configuration
��    �� �� ʱ������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void RCC_Configuration(void)
{
  /* ʹ��AHB1ʱ�� */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                         RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | 
                         RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | 
                         RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH, ENABLE);

  /* ʹ��APB1ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4 | 
                         RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM5, ENABLE);

  /* ʹ��APB2ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

#if 0
   /* ʹ��APB3ʱ�� */
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
#endif
}

/************************************************
�������� �� GPIO_Basic_Configuration
��    �� �� �������������������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void GPIO_Basic_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure1;
  GPIO_InitTypeDef GPIO_InitStructure2;

  /* LED���� */
  GPIO_InitStructure.GPIO_Pin = PIN_LED;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(PORT_LED, &GPIO_InitStructure);
  
  /* �ж����� */
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOD, &GPIO_InitStructure1);
  
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOE, &GPIO_InitStructure1); 
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource0);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);
  
  /* ��ѹת����־���� */
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOB, &GPIO_InitStructure1);
  
  /* ADC���� */
  GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&GPIO_InitStructure2);
  
  /* oled�˿ڳ�ʼ�� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  
  
  /* ������ */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                |GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  /* read/write */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* cs/dc */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
#if 0
  /* ʱ����� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_2);
#endif
}

/************************************************
�������� �� NVIC_Configuration
��    �� �� NVIC����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* �����ж� */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                  //IRQͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;          //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                 //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                    //ʹ��ͨ��
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                    //IRQͨ��:��ʱ��3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;                  // IRQͨ����EXTI0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_Init(&NVIC_InitStructure);
}

/************************************************
�������� �� GPIO_EXTILineConfig
��    �� �� GPIO�ж�����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� mark
*************************************************/
void GPIO_EXTILineConfig(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure; 
  EXTI_InitStructure.EXTI_Line=EXTI_Line0; 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
  EXTI_Init(&EXTI_InitStructure);     //��ʼ������EXTI0�Ĵ���
  
  EXTI_InitStructure.EXTI_Line=EXTI_Line1; 
  EXTI_Init(&EXTI_InitStructure);     //��ʼ������EXTI1�Ĵ���
}


/************************************************
�������� �� BSP_Initializes
��    �� �� �ײ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void BSP_Initializes(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_Configuration();                                              //NVIC����
  RCC_Configuration();                                               //ʱ������
  GPIO_Basic_Configuration();                                        //IO����
  GPIO_EXTILineConfig();                                             //EXTI����
  
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
