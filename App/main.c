/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� main.c
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� ������ - TIM��ʱ�����벶������(Ƶ�ʡ�ռ�ձ�)
                   ��������������ʱ�����Ƶ�ʡ�ռ�ձ�
                   ����Ƶ�ʷ�Χ��1Hz - 500KHz
                   ����ռ�ձȷ�Χ:1% - 99%
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-07-12 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include <stdlib.h>
#include "bsp.h"
#include "timer.h"
#include "usart.h"
#include "global_variable.h"
#include "adc.h"
#include "oled.h"

#define SIZE (50)

/************************************************
�������� �� System_Initializes
��    �� �� ϵͳ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void System_Initializes(void)
{
  BSP_Initializes();
  TIMER_Initializes();
  ADC_Initializes();
  USART_Initializes();
  OLED_Init();
}

/* ����ADC���� */
void Get_Data(void)
{
  int i;
  ADC_SoftwareStartConv(ADC1);                   // �������ADC
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
�������� �� main
��    �� �� ���������
��    �� �� ��
�� �� ֵ �� int
��    �� �� strongerHuang
*************************************************/
int main(void)
{
  System_Initializes();
	   
  TIM2_CH2_PWM(1000000, 10);                     //���1MHz��ռ�ձ�10%��PWM����
  
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
    LED_TOGGLE;                 //LED�仯   
  
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
