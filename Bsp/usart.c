/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： usart.c
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： USART源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-07-12 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "usart.h"


/************************************************
函数名称 ： USART_GPIO_Configuration
功    能 ： USART所使用管脚输出输入定义
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void USART_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  /* 定义USART-TX 引脚为复用输出 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                          //IO口的第9脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //IO口速度
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //IO口复用
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);                             //USART1输出IO口

  /* 定义 USART-Rx 引脚为悬空输入 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                         //IO口的第10脚
  GPIO_Init(GPIOA, &GPIO_InitStructure);                             //USART1输入IO口
}

/************************************************
函数名称 ： USART_Configuration
功    能 ： 配置USART
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  /******************************************************************
   USART参数初始化:  波特率     传输位数   停止位数  校验位数
                     115200        8          1       0(NO)
  *******************************************************************/
  USART_InitStructure.USART_BaudRate = 115200;                       //设定传输速率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //设定传输数据位数
  USART_InitStructure.USART_StopBits = USART_StopBits_1;             //设定停止位个数
  USART_InitStructure.USART_Parity = USART_Parity_No ;               //不用校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不用流量控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //使用接收和发送功能
  USART_Init(USART1, &USART_InitStructure);                          //初始化USART1

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                     //使能USART1接收中断

  USART_Cmd(USART1, ENABLE);                                         //使能USART1
}

/************************************************
函数名称 ： USART_Initializes
功    能 ： 串口初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void USART_Initializes(void)
{
  USART_GPIO_Configuration();
  USART_Configuration();
}

/************************************************
函数名称 ： USART1_SendChar
功    能 ： 串口1发送一个字符
参    数 ： Data --- 数据
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void USART1_SendByte(uint8_t Data)
{
  USART_SendData(USART1, (uint8_t)Data);         //发送数据, 并等待发送完成(USART_FLAG_TC)
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/************************************************
函数名称 ： USART1_SendNByte
功    能 ： 串口1发送N个字符
参    数 ： pData ---- 字符串
            Length --- 长度
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void USART1_SendNByte(uint8_t *pData, uint16_t Length)
{
  while(Length--)
  {
    USART1_SendByte(*pData);
    pData++;
  }
}

/************************************************
函数名称 ： USART1_SendString
功    能 ： 串口1发送一串字符
参    数 ： string --- 字符串
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void USART1_SendString(uint8_t *String)
{
  while((*String) != '\0')
  {
    USART1_SendByte(*String);
    String++;
  }
  USART1_SendByte(0x0A);                         //换行
}

/******************************************* 串口重定义 *******************************************/
/************************************************
函数名称 ： fputc
功    能 ： 重定义putc函数
参    数 ： ch --- 字符
            *f --- 文件指针
返 回 值 ： 字符
作    者 ： strongerHuang
*************************************************/
int fputc(int ch, FILE *f)
{
  USART1_SendByte((uint8_t)ch);

  return ch;
}

/************************************************
函数名称 ： fgetc
功    能 ： 重定义getc函数
参    数 ： *f --- 文件指针
返 回 值 ： 字符
作    者 ： strongerHuang
*************************************************/
int fgetc(FILE *f)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(USART1);
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
