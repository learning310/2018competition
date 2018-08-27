/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： timer.c
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： 定时器源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-07-12 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "timer.h"


/************************************************
函数名称 ： TIMER_Initializes
功    能 ： TIMER初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* TIM4时基单元配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM4_PRESCALER_VALUE;        //预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = TIM4_PERIOD_TIMING;             //定时周期
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  TIMER1_Initializes();                                               //TIMER1初始化
  TIMER_PWM_GPIO_Configuration();                                    // pwm输出
  TIMER_IC_Initializes();                                            //(增加)PWM配置
}

/************************************************
函数名称 ： TIMER1_Initializes
功    能 ： TIMER初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： mark
*************************************************/
void TIMER1_Initializes(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* TIM1时基单元配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
}

/************************************************
函数名称 ： TIMDelay_Nus
功    能 ： 定时器延时N微秒(阻塞式)
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_Nus(uint16_t Times)
{
  TIM_Cmd(TIM4, ENABLE);                                             //启动定时器
  while(Times--)
  {
    while(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) == RESET);        //等待计数完成
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);                            //清除标志
  }
  TIM_Cmd(TIM4, DISABLE);                                            //关闭定时器
}

/************************************************
函数名称 ： TIMDelay_Nms
功    能 ： 定时器延时N毫秒
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_Nus(1000);
  }
}

/****************************************** 比较输出 PWM ******************************************/
/************************************************
函数名称 ： TIMER_PWM_GPIO_Configuration
功    能 ： 定时器输出PWM引脚配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_PWM_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                          //输出引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //复用模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                 //高速输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                     //推完输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                       //上拉 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);            //复用配置
}


/************************************************
函数名称 ： TIM2_CH2_PWM
功    能 ： 定时器2通道2输出PWM
参    数 ： Freq -------- 频率
            Dutycycle --- 占空比
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIM2_CH2_PWM(uint32_t Freq, uint16_t Dutycycle)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  uint32_t tim2_period;
  uint32_t tim2_pulse;

  tim2_period = TIM2_COUNTER_CLOCK/Freq - 1;                         //计算出计数周期(决定输出的频率)
  tim2_pulse  = (tim2_period + 1)*Dutycycle / 100;                   //计算出脉宽值(决定PWM占空比)

  /* TIM2时基单元配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM2_PRESCALER_VALUE;        //预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = tim2_period;                    //定时周期(自动从装载寄存器ARR的值)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* TIM2通道2:PWM1模式配置 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                  //输出PWM1模式
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //使能输出
  TIM_OCInitStructure.TIM_Pulse = tim2_pulse;                        //脉宽值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //输出极性
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_Cmd(TIM2, ENABLE);                                             //使能TIM2
}


/******************************************** 输入捕获 ********************************************/
/************************************************
函数名称 ： TIMER_IC_GPIO_Configuration
功    能 ： 定时器输入捕获引脚配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_IC_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;             //捕获引脚(输入波形引脚)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //复用模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //无上下拉(浮空)
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);            //复用配置
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);            //复用配置
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //捕获引脚(输入波形引脚)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //复用模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                   //无上下拉(浮空)
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);            //复用配置
}

/************************************************
函数名称 ： TIMER_IC_Configuration
功    能 ： 定时器输入捕获配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_IC_Configuration(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0;                           //不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;                     //定时周期(自动从装载寄存器ARR的值)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;                   //通道1
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;        //捕获极性(上升沿)
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;    //捕获选择
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV4;              //捕获分频
  TIM_ICInitStructure.TIM_ICFilter = 0;                              //捕获滤波
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                   //通道2
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;       //捕获极性(下降沿)
  TIM_ICInit(TIM3, &TIM_ICInitStructure);

  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                            //使能中断
  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);                            //使能中断
  
  TIM_Cmd(TIM3, ENABLE); 
}

void TIMER5_IC_Configuration(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  TIM_TimeBaseStructure.TIM_Prescaler = 0;                           //不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;                     //定时周期(自动从装载寄存器ARR的值)
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;                   //通道4
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;        //捕获极性(上升沿)
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;    //捕获选择
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;              //捕获分频
  TIM_ICInitStructure.TIM_ICFilter = 0;                              //捕获滤波
  TIM_ICInit(TIM5, &TIM_ICInitStructure);

  TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);                            //使能中断
	
	TIM_Cmd(TIM5, ENABLE);                                             //使能TIM5
}

/************************************************
函数名称 ： TIMER_IC_Initializes
功    能 ： 定时器输入捕获初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_IC_Initializes(void)
{
  TIMER_IC_GPIO_Configuration();
  TIMER_IC_Configuration();
	TIMER5_IC_Configuration();
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
