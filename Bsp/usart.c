/**
  ********************************  STM32F4xx  *********************************
  * @�ļ���     �� usart.c
  * @����       �� strongerHuang
  * @��汾     �� V1.7.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��07��12��
  * @ժҪ       �� USARTԴ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-07-12 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "usart.h"


/************************************************
�������� �� USART_GPIO_Configuration
��    �� �� USART��ʹ�ùܽ�������붨��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  /* ����USART-TX ����Ϊ������� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                          //IO�ڵĵ�9��
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //IO���ٶ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //IO�ڸ���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);                             //USART1���IO��

  /* ���� USART-Rx ����Ϊ�������� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                         //IO�ڵĵ�10��
  GPIO_Init(GPIOA, &GPIO_InitStructure);                             //USART1����IO��
}

/************************************************
�������� �� USART_Configuration
��    �� �� ����USART
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  /******************************************************************
   USART������ʼ��:  ������     ����λ��   ֹͣλ��  У��λ��
                     115200        8          1       0(NO)
  *******************************************************************/
  USART_InitStructure.USART_BaudRate = 115200;                       //�趨��������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //�趨��������λ��
  USART_InitStructure.USART_StopBits = USART_StopBits_1;             //�趨ֹͣλ����
  USART_InitStructure.USART_Parity = USART_Parity_No ;               //����У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//������������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //ʹ�ý��պͷ��͹���
  USART_Init(USART1, &USART_InitStructure);                          //��ʼ��USART1

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                     //ʹ��USART1�����ж�

  USART_Cmd(USART1, ENABLE);                                         //ʹ��USART1
}

/************************************************
�������� �� USART_Initializes
��    �� �� ���ڳ�ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_Initializes(void)
{
  USART_GPIO_Configuration();
  USART_Configuration();
}

/************************************************
�������� �� USART1_SendChar
��    �� �� ����1����һ���ַ�
��    �� �� Data --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART1_SendByte(uint8_t Data)
{
  USART_SendData(USART1, (uint8_t)Data);         //��������, ���ȴ��������(USART_FLAG_TC)
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/************************************************
�������� �� USART1_SendNByte
��    �� �� ����1����N���ַ�
��    �� �� pData ---- �ַ���
            Length --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
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
�������� �� USART1_SendString
��    �� �� ����1����һ���ַ�
��    �� �� string --- �ַ���
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART1_SendString(uint8_t *String)
{
  while((*String) != '\0')
  {
    USART1_SendByte(*String);
    String++;
  }
  USART1_SendByte(0x0A);                         //����
}

/******************************************* �����ض��� *******************************************/
/************************************************
�������� �� fputc
��    �� �� �ض���putc����
��    �� �� ch --- �ַ�
            *f --- �ļ�ָ��
�� �� ֵ �� �ַ�
��    �� �� strongerHuang
*************************************************/
int fputc(int ch, FILE *f)
{
  USART1_SendByte((uint8_t)ch);

  return ch;
}

/************************************************
�������� �� fgetc
��    �� �� �ض���getc����
��    �� �� *f --- �ļ�ָ��
�� �� ֵ �� �ַ�
��    �� �� strongerHuang
*************************************************/
int fgetc(FILE *f)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(USART1);
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
