#include "led.h"
#include "ALL_Includes.h"

/****************************************************
�������ܣ�LED��ʼ��
�����������
�����������
��    ע�����ô˺���ǰ����Ҫ��LED.h�޸ĺ궨��LED����
****************************************************/
void LED_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(LED_GPIO_CLK, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin = LED_PIN1|LED_PIN2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

/****************************************************
�������ܣ�LED��
���������1 LED1, 2 LED2
�����������
��    ע�����ô˺���ǰ����Ҫ��LED.h�޸ĺ궨��LED����
****************************************************/
void LED_ON(u8 res)
{
	if(res==1)
	{
		GPIO_SetBits(LED_PORT, LED_PIN1);
	}
	else if(res==2)
	{
		GPIO_SetBits(LED_PORT, LED_PIN2);		
	}
}

/****************************************************
�������ܣ�LED��
���������1  LED1 ,2 LED2
�����������
��    ע�����ô˺���ǰ����Ҫ��LED.h�޸ĺ궨��LED����
****************************************************/
void LED_OFF(u8 res)
{
	if(res==1)
	{
		GPIO_ResetBits(LED_PORT, LED_PIN1);
	}
	else if(res==2)
	{
		GPIO_ResetBits(LED_PORT, LED_PIN2);		
	}
}

