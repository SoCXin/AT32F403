

/*
	Ӧ��˵����
	�ڷ���I2C�豸ǰ�����ȵ��� i2c_CheckDevice() ���I2C�豸�Ƿ��������ú���������GPIO
*/

//#include "stm32f10x.h"
#include "ALL_Includes.h"
#include "bsp_i2c.h"

/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define GPIO_PORT_I2C	GPIOA			/* GPIO�˿� */
#define RCC_I2C_PORT 	RCC_AHBPeriph_GPIOA		/* GPIO�˿�ʱ�� */
#define L_I2C_SCL_PIN		GPIO_Pin_2			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define L_I2C_SDA_PIN		GPIO_Pin_1			/* ���ӵ�SDA�����ߵ�GPIO */

/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */

	#define L_I2C_SCL_1()  GPIO_PORT_I2C->BSRR = L_I2C_SCL_PIN				/* SCL = 1 */
	#define L_I2C_SCL_0()  GPIO_PORT_I2C->BRR = L_I2C_SCL_PIN				/* SCL = 0 */
	
	#define L_I2C_SDA_1()  GPIO_PORT_I2C->BSRR = L_I2C_SDA_PIN				/* SDA = 1 */
	#define L_I2C_SDA_0()  GPIO_PORT_I2C->BRR = L_I2C_SDA_PIN				/* SDA = 0 */
	
	#define L_I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & L_I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
//#endif


/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
//#define R_GPIO_PORT_I2C	GPIOA			/* GPIO�˿� */
//#define R_RCC_I2C_PORT 	RCC_AHBPeriph_GPIOA		/* GPIO�˿�ʱ�� */
#define R_I2C_SCL_PIN		GPIO_Pin_4			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define R_I2C_SDA_PIN		GPIO_Pin_3			/* ���ӵ�SDA�����ߵ�GPIO */

	#define R_I2C_SCL_1()  GPIO_PORT_I2C->BSRR = R_I2C_SCL_PIN				/* SCL = 1 */
	#define R_I2C_SCL_0()  GPIO_PORT_I2C->BRR = R_I2C_SCL_PIN				/* SCL = 0 */
	
	#define R_I2C_SDA_1()  GPIO_PORT_I2C->BSRR = R_I2C_SDA_PIN				/* SDA = 1 */
	#define R_I2C_SDA_0()  GPIO_PORT_I2C->BRR = R_I2C_SDA_PIN				/* SDA = 0 */
	
	#define R_I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & R_I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
//#endif

void L_i2c_GPIO_Config(void);
void R_i2c_GPIO_Config(void);
/*
*********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//static void i2c_Delay(void)
//{
//	uint8_t i;

//	/*��
//	 	�����ʱ����ͨ��������AX-Pro�߼������ǲ��Եõ��ġ�
//		CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
//		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
//		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
//	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
//        
//    IAR���̱���Ч�ʸߣ���������Ϊ7
//	*/
//	for (i = 0; i < 10; i++);
//}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C���������ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void L_i2c_Start(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
	L_I2C_SDA_1();
	L_I2C_SCL_1();
//	i2c_Delay();
	__nop();
	L_I2C_SDA_0();
//	i2c_Delay();
	__nop();
	L_I2C_SCL_0();
//	i2c_Delay();
	__nop();
}
void R_i2c_Start(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
	R_I2C_SDA_1();
	R_I2C_SCL_1();
//	i2c_Delay();
	__nop();
	R_I2C_SDA_0();
//	i2c_Delay();
	__nop();
	R_I2C_SCL_0();
//	i2c_Delay();
	__nop();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void L_i2c_Stop(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	L_I2C_SDA_0();
	L_I2C_SCL_1();
//	i2c_Delay();
	__nop();
	L_I2C_SDA_1();
}
void R_i2c_Stop(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	R_I2C_SDA_0();
	R_I2C_SCL_1();
//	i2c_Delay();
	__nop();
	R_I2C_SDA_1();
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void L_i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			L_I2C_SDA_1();
		}
		else
		{
			L_I2C_SDA_0();
		}
//		i2c_Delay();
		__nop();
		L_I2C_SCL_1();
//		i2c_Delay();
		__nop(); 
		L_I2C_SCL_0();
		if (i == 7)
		{
			 L_I2C_SDA_1(); // �ͷ�����
		}
		_ucByte <<= 1;	/* ����һ��bit */
//		i2c_Delay();
		__nop();
	}
}
void R_i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			R_I2C_SDA_1();
		}
		else
		{
			R_I2C_SDA_0();
		}
//		i2c_Delay();
		__nop();
		R_I2C_SCL_1();
//		i2c_Delay();
		__nop(); 
		R_I2C_SCL_0();
		if (i == 7)
		{
			 R_I2C_SDA_1(); // �ͷ�����
		}
		_ucByte <<= 1;	/* ����һ��bit */
//		i2c_Delay();
		__nop();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
uint8_t L_i2c_ReadByte(u8 ack)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		L_I2C_SCL_1();
//		i2c_Delay();
		__nop();
		if (L_I2C_SDA_READ())
		{
			value++;
		}
		L_I2C_SCL_0();
//		i2c_Delay();
		__nop();
	}
	if(ack==0)
		L_i2c_NAck();
	else
		L_i2c_Ack();
	return value;
}
uint8_t R_i2c_ReadByte(u8 ack)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		R_I2C_SCL_1();
//		i2c_Delay();
		__nop();
		if (R_I2C_SDA_READ())
		{
			value++;
		}
		R_I2C_SCL_0();
//		i2c_Delay();
		__nop();
	}
	if(ack==0)
		R_i2c_NAck();
	else
		R_i2c_Ack();
	return value;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
uint8_t L_i2c_WaitAck(void)
{
	uint8_t re;

	L_I2C_SDA_1();	/* CPU�ͷ�SDA���� */
//	i2c_Delay();
	__nop();
	L_I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
//	i2c_Delay();
	__nop();
	if (L_I2C_SDA_READ())	/* CPU��ȡSDA����״̬ */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	L_I2C_SCL_0();
//	i2c_Delay();
	__nop();
	return re;
}
uint8_t R_i2c_WaitAck(void)
{
	uint8_t re;

	R_I2C_SDA_1();	/* CPU�ͷ�SDA���� */
//	i2c_Delay();
	__nop();
	R_I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
//	i2c_Delay();
	__nop();
	if (R_I2C_SDA_READ())	/* CPU��ȡSDA����״̬ */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	R_I2C_SCL_0();
//	i2c_Delay();
	__nop();
	return re;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void L_i2c_Ack(void)
{
	L_I2C_SDA_0();	/* CPU����SDA = 0 */
//	i2c_Delay();
	__nop();__nop();
	L_I2C_SCL_1();	/* CPU����1��ʱ�� */
//	i2c_Delay();
	__nop();__nop();
	L_I2C_SCL_0();
//	i2c_Delay();
	__nop();__nop();
	L_I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}
void R_i2c_Ack(void)
{
	R_I2C_SDA_0();	/* CPU����SDA = 0 */
//	i2c_Delay();
	__nop();__nop();
	R_I2C_SCL_1();	/* CPU����1��ʱ�� */
//	i2c_Delay();
	__nop();__nop();
	R_I2C_SCL_0();
//	i2c_Delay();
	__nop();__nop();
	R_I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void L_i2c_NAck(void)
{
	L_I2C_SDA_1();	/* CPU����SDA = 1 */
//	i2c_Delay();
	__nop();__nop();
	L_I2C_SCL_1();	/* CPU����1��ʱ�� */
//	i2c_Delay();
	__nop();__nop();
	L_I2C_SCL_0();
//	i2c_Delay();	
	__nop();__nop();
}
void R_i2c_NAck(void)
{
	R_I2C_SDA_1();	/* CPU����SDA = 1 */
//	i2c_Delay();
	__nop();__nop();
	R_I2C_SCL_1();	/* CPU����1��ʱ�� */
//	i2c_Delay();
	__nop();__nop();
	R_I2C_SCL_0();
//	i2c_Delay();	
	__nop();__nop();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_GPIO_Config
*	����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void L_i2c_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* ��GPIOʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);

	GPIO_InitStructure.GPIO_Pin = L_I2C_SCL_PIN | L_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* ��©��� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;	
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
	L_i2c_Stop();
}

void R_i2c_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* ��GPIOʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);

	GPIO_InitStructure.GPIO_Pin = R_I2C_SCL_PIN | R_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* ��©��� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;	
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
	R_i2c_Stop();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_CheckDevice
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    �Σ�_Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
*********************************************************************************************************
*/
uint8_t L_i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	L_i2c_GPIO_Config();		/* ����GPIO */
	
	L_i2c_Start();		/* ���������ź� */

	/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
	L_i2c_SendByte(_Address|I2C_WR);
	ucAck = L_i2c_WaitAck();	/* ����豸��ACKӦ�� */

	L_i2c_Stop();			/* ����ֹͣ�ź� */

	return ucAck;
}

uint8_t R_i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	R_i2c_GPIO_Config();		/* ����GPIO */
	
	R_i2c_Start();		/* ���������ź� */

	/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
	R_i2c_SendByte(_Address|I2C_WR);
	ucAck = R_i2c_WaitAck();	/* ����豸��ACKӦ�� */

	R_i2c_Stop();			/* ����ֹͣ�ź� */

	return ucAck;
}



