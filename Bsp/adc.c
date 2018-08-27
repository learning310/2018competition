/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� adc.h
  * @����       �� mark
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2018��07��31��
  * @ժҪ       �� ADCԴ�ļ�
  ******************************************************************************/

/* ������ͷ�ļ� */
#include "adc.h"

/************************************************
�������� �� ADC_Initializes
��    �� �� TIMER��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void ADC_Initializes(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;      // ����ģʽ
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;   // ��Ƶϵ��
  ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled; // �ر�DMA
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  // �������
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;   // �ر�ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // ����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // ���Բ����ô���ģʽ
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    // ���ݶ��䷽ʽ �Ҷ���
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  ADC_RegularChannelConfig(ADC1, 4, 1, ADC_SampleTime_144Cycles);
  ADC_Cmd(ADC1, ENABLE);
  
}

