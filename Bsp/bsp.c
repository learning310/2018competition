/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： bsp.c
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： BSP板级支持包源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-07-12 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
函数名称 ： RCC_Configuration
功    能 ： 时钟配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void RCC_Configuration(void)
{
  /* 使能AHB1时钟 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                         RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | 
                         RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | 
                         RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH, ENABLE);

  /* 使能APB1时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4 | 
                         RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM5, ENABLE);

  /* 使能APB2时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

#if 0
   /* 使能APB3时钟 */
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
#endif
}

/************************************************
函数名称 ： GPIO_Basic_Configuration
功    能 ： 基本输入输出引脚配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void GPIO_Basic_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure1;
  GPIO_InitTypeDef GPIO_InitStructure2;

  /* LED引脚 */
  GPIO_InitStructure.GPIO_Pin = PIN_LED;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(PORT_LED, &GPIO_InitStructure);
  
  /* 中断引脚 */
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOD, &GPIO_InitStructure1);
  
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOE, &GPIO_InitStructure1); 
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource0);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);
  
  /* 电压转换标志引脚 */
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(GPIOB, &GPIO_InitStructure1);
  
  /* ADC引脚 */
  GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&GPIO_InitStructure2);
  
  /* oled端口初始化 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  
  
  /* 数据线 */
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
  /* 时钟输出 */
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
函数名称 ： NVIC_Configuration
功    能 ： NVIC配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 外设中断 */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                  //IRQ通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;          //主优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                 //从优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                    //使能通道
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                    //IRQ通道:定时器3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;                  // IRQ通道：EXTI0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_Init(&NVIC_InitStructure);
}

/************************************************
函数名称 ： GPIO_EXTILineConfig
功    能 ： GPIO中断配置
参    数 ： 无
返 回 值 ： 无
作    者 ： mark
*************************************************/
void GPIO_EXTILineConfig(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure; 
  EXTI_InitStructure.EXTI_Line=EXTI_Line0; 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
  EXTI_Init(&EXTI_InitStructure);     //初始化外设EXTI0寄存器
  
  EXTI_InitStructure.EXTI_Line=EXTI_Line1; 
  EXTI_Init(&EXTI_InitStructure);     //初始化外设EXTI1寄存器
}


/************************************************
函数名称 ： BSP_Initializes
功    能 ： 底层初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void BSP_Initializes(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_Configuration();                                              //NVIC配置
  RCC_Configuration();                                               //时钟配置
  GPIO_Basic_Configuration();                                        //IO配置
  GPIO_EXTILineConfig();                                             //EXTI配置
  
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
