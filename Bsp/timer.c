/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� timer.c
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� ��ʱ��Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-07-12 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "timer.h"


/************************************************
�������� �� TIMER_Initializes
��    �� �� TIMER��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* TIM4ʱ����Ԫ���� */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM4_PRESCALER_VALUE;        //Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = TIM4_PERIOD_TIMING;             //��ʱ����
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  TIMER1_Initializes();                                               //TIMER1��ʼ��
  TIMER_PWM_GPIO_Configuration();                                    // pwm���
  TIMER_IC_Initializes();                                            //(����)PWM����
}

/************************************************
�������� �� TIMER1_Initializes
��    �� �� TIMER��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� mark
*************************************************/
void TIMER1_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* TIM1ʱ����Ԫ���� */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
}

/************************************************
�������� �� TIMDelay_Nus
��    �� �� ��ʱ����ʱN΢��(����ʽ)
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_Nus(uint16_t Times)
{
  TIM_Cmd(TIM4, ENABLE);                                             //������ʱ��
  while(Times--)
  {
    while(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) == RESET);        //�ȴ��������
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);                            //�����־
  }
  TIM_Cmd(TIM4, DISABLE);                                            //�رն�ʱ��
}

/************************************************
�������� �� TIMDelay_Nms
��    �� �� ��ʱ����ʱN����
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_Nus(1000);
  }
}

/****************************************** �Ƚ���� PWM ******************************************/
/************************************************
�������� �� TIMER_PWM_GPIO_Configuration
��    �� �� ��ʱ�����PWM��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_PWM_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                          //�������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                 //�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //�������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                       //���� 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);            //��������
}


/************************************************
�������� �� TIM2_CH2_PWM
��    �� �� ��ʱ��2ͨ��2���PWM
��    �� �� Freq -------- Ƶ��
            Dutycycle --- ռ�ձ�
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIM2_CH2_PWM(uint32_t Freq, uint16_t Dutycycle)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  uint32_t tim2_period;
  uint32_t tim2_pulse;

  tim2_period = TIM2_COUNTER_CLOCK/Freq - 1;                         //�������������(���������Ƶ��)
  tim2_pulse  = (tim2_period + 1)*Dutycycle / 100;                   //���������ֵ(����PWMռ�ձ�)

  /* TIM2ʱ����Ԫ���� */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM2_PRESCALER_VALUE;        //Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = tim2_period;                    //��ʱ����(�Զ���װ�ؼĴ���ARR��ֵ)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* TIM2ͨ��2:PWM1ģʽ���� */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                  //���PWM1ģʽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //ʹ�����
  TIM_OCInitStructure.TIM_Pulse = tim2_pulse;                        //����ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //�������
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_Cmd(TIM2, ENABLE);                                             //ʹ��TIM2
}


/******************************************** ���벶�� ********************************************/
/************************************************
�������� �� TIMER_IC_GPIO_Configuration
��    �� �� ��ʱ�����벶����������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_IC_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;             //��������(���벨������)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //����ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //��������(����)
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);            //��������
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);            //��������
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //��������(���벨������)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //����ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //��������(����)
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);            //��������
}

/************************************************
�������� �� TIMER_IC_Configuration
��    �� �� ��ʱ�����벶������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_IC_Configuration(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0;                           //����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;                     //��ʱ����(�Զ���װ�ؼĴ���ARR��ֵ)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;                   //ͨ��1
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;        //������(������)
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;    //����ѡ��
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV4;              //�����Ƶ
  TIM_ICInitStructure.TIM_ICFilter = 0;                              //�����˲�
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                   //ͨ��2
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;       //������(�½���)
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                            //ʹ���ж�
  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);                            //ʹ���ж�
  
  TIM_Cmd(TIM3, ENABLE); 
}

void TIMER5_IC_Configuration(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0;                           //����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;                     //��ʱ����(�Զ���װ�ؼĴ���ARR��ֵ)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;                   //ͨ��4
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;        //������(������)
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;    //����ѡ��
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;              //�����Ƶ
  TIM_ICInitStructure.TIM_ICFilter = 0;                              //�����˲�
  TIM_ICInit(TIM5, &TIM_ICInitStructure);

  TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);                            //ʹ���ж�
	
	TIM_Cmd(TIM5, ENABLE);                                             //ʹ��TIM5
}

/************************************************
�������� �� TIMER_IC_Initializes
��    �� �� ��ʱ�����벶���ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_IC_Initializes(void)
{
  TIMER_IC_GPIO_Configuration();
  TIMER_IC_Configuration();
	TIMER5_IC_Configuration();
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
