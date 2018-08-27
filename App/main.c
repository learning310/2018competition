/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： main.c
  * @作者       ： strongerHuang
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2016年07月12日
  * @摘要       ： 主函数 - TIM定时器输入捕获脉冲(频率、占空比)
                   利用输入脉冲间隔时间计算频率、占空比
                   输入频率范围：1Hz - 500KHz
                   输入占空比范围:1% - 99%
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2016-07-12 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include <stdlib.h>
#include "bsp.h"
#include "timer.h"
#include "usart.h"
#include "global_variable.h"
#include "adc.h"
#include "oled.h"

#define SIZE (50)

/************************************************
函数名称 ： System_Initializes
功    能 ： 系统初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void System_Initializes(void)
{
  BSP_Initializes();
  TIMER_Initializes();
  ADC_Initializes();
  USART_Initializes();
  OLED_Init();
}

/* 处理ADC数据 */
void Get_Data(void)
{
  int i;
  ADC_SoftwareStartConv(ADC1);                   // 软件启动ADC
  for (i=0; i<SIZE; i++){
    data[i] = ADC_GetConversionValue(ADC1);
    ADC1->SR &= ~ADC_SR_EOC;
  }
}

uint32_t proc_data(void)
{
  uint32_t max = 0,i;
  max = (uint32_t)data[0];
  for(i=1; i<SIZE; i++)
  {
    if( data[i] > max )
       max = (uint32_t)data[i];
  }
  max = (max*3300)/4096;
	if(max < 200)
		max = max + (max/10)*5;
	else if(max < 500)
		max = max + (max/10)*3;
	else if(max < 1200)
		max = max + (max/10)*2;
	else if(max < 2000)
		max = max + (max%100);
	else if (max < 3300)
		max = max + 80;
	
  if( (GPIOB->ODR&0x800) > 0)
    max = max*2;
  else if( (GPIOB->ODR&0x1000) > 0)
    max = max*3;
	
	return max;
}

/************************************************
函数名称 ： main
功    能 ： 主函数入口
参    数 ： 无
返 回 值 ： int
作    者 ： strongerHuang
*************************************************/
int main(void)
{
  System_Initializes();
	   
  TIM2_CH2_PWM(1000000, 10);                     //输出1MHz、占空比10%的PWM波形
  
  OLED_ShowString(0,0, "Freq:",16); 
  OLED_ShowString(0,16,"Duty:",16);
  OLED_ShowString(0,32,"Rise:",16);
  OLED_ShowString(0,48,"Max :",16);
  OLED_ShowString(120,0,"H",16);
  OLED_ShowString(120,16,"%",16);
  OLED_ShowString(120,32,"n",16);
  OLED_ShowString(120,48,"m",16);
  
  while(1)
  {
    LED_TOGGLE;                 //LED变化   
  
    Get_Data();
		Max = proc_data();
    Rise = Rise * 10;
		
    OLED_ShowNum(40,0, (uint32_t)Freq_InputCapture,10,16);
    OLED_ShowNum(40,16,(uint32_t)DutyCycle_InputCapture,10,16);
    OLED_ShowNum(40,32,(uint32_t)Rise,4,16);
    OLED_ShowNum(40,48,(uint32_t)Max,10,16);
    OLED_Refresh_Gram();
    
    TIMDelay_Nms(100);
  }
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
