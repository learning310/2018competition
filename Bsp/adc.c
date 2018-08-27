/**
  ********************************  STM32F4xx  *********************************
  * @文件名     ： adc.h
  * @作者       ： mark
  * @库版本     ： V1.7.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2018年07月31日
  * @摘要       ： ADC源文件
  ******************************************************************************/

/* 包含的头文件 */
#include "adc.h"

/************************************************
函数名称 ： ADC_Initializes
功    能 ： TIMER初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void ADC_Initializes(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;      // 独立模式
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;   // 分频系数
  ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled; // 关闭DMA
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  // 采样间隔
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;   // 关闭扫描模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // 连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // 测试不采用触发模式
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    // 数据对其方式 右对齐
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  ADC_RegularChannelConfig(ADC1, 4, 1, ADC_SampleTime_144Cycles);
  ADC_Cmd(ADC1, ENABLE);
  
}

