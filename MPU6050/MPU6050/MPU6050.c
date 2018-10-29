//#include "delay.h"
//#include "myiic.h"
#include "MPU6050.h"
#include "ALL_Includes.h"
#include "bsp_i2c.h"


void Delay_us(u32 dly)
{
	u8 i;
	while(dly--) for(i=0;i<10;i++);
}
//
void Delay_ms(u32 dly)
{
	while(dly--) Delay_us(1000);
}



void MPU6050_Init(void)		
{
  L_i2c_GPIO_Config();   //��ʼ��IIC����
//	L_Init_MPU_6050();		//��ʼ��MPU6050 
  R_i2c_GPIO_Config();   //��ʼ��IIC����
//	R_Init_MPU_6050();		//��ʼ��MPU6050 	
	Init_MPU_6050();		//��ʼ��MPU6050 
}

void L_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_Data)
{
	L_i2c_Start();					//��ʼ�ź�
	L_i2c_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	L_i2c_WaitAck(); 				//�ȴ�Ӧ��
	L_i2c_SendByte(REG_Address);		//�����豸�Ĵ�����ַ
	L_i2c_WaitAck(); 				//�ȴ�Ӧ��
	L_i2c_SendByte(REG_Data);		//д����
	L_i2c_WaitAck(); 				//�ȴ�Ӧ��
	L_i2c_Stop();						//ֹͣ�ź�
//	Delay_ms(5);
	__nop();__nop();__nop();__nop();
}

void R_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_Data)
{
	R_i2c_Start();					//��ʼ�ź�
	R_i2c_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	R_i2c_WaitAck(); 				//�ȴ�Ӧ��
	R_i2c_SendByte(REG_Address);		//�����豸�Ĵ�����ַ
	R_i2c_WaitAck(); 				//�ȴ�Ӧ��
	R_i2c_SendByte(REG_Data);		//д����
	R_i2c_WaitAck(); 				//�ȴ�Ӧ��
	R_i2c_Stop();						//ֹͣ�ź�
//	Delay_ms(5);
	__nop();__nop();__nop();__nop();
}

u8 L_Single_Read(u8 SlaveAddress,u8 REG_Address)
{
	u8 REG_Data;
	L_i2c_Start();					//��ʼ�ź�
	L_i2c_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	L_i2c_WaitAck();  				//�ȴ�Ӧ��
	L_i2c_SendByte(REG_Address);    //�����豸�Ĵ�����ַ
	L_i2c_WaitAck();  				//�ȴ�Ӧ��
	L_i2c_Start();					//�ٴο�ʼ�ź�
	L_i2c_SendByte(SlaveAddress + 1);    //�����豸��ַ+���ź�
	L_i2c_WaitAck();    			//�ȴ�Ӧ��
	REG_Data = L_i2c_ReadByte(1);		//��ȡ����
	L_i2c_NAck();						//����Ӧ��
	L_i2c_Stop();						//ֹͣ�ź�
//	Delay_ms(5);	
  __nop();__nop();__nop();__nop();
	return REG_Data;			
}

u8 R_Single_Read(u8 SlaveAddress,u8 REG_Address)
{
	u8 REG_Data;
	R_i2c_Start();					//��ʼ�ź�
	R_i2c_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	R_i2c_WaitAck();  				//�ȴ�Ӧ��
	R_i2c_SendByte(REG_Address);    //�����豸�Ĵ�����ַ
	R_i2c_WaitAck();  				//�ȴ�Ӧ��
	R_i2c_Start();					//�ٴο�ʼ�ź�
	R_i2c_SendByte(SlaveAddress + 1);    //�����豸��ַ+���ź�
	R_i2c_WaitAck();    			//�ȴ�Ӧ��
	REG_Data = R_i2c_ReadByte(1);		//��ȡ����
	R_i2c_NAck();						//����Ӧ��
	R_i2c_Stop();						//ֹͣ�ź�
//	Delay_ms(5);	
  __nop();__nop();__nop();__nop();
	return REG_Data;			
}

//u8 L_MPU6050_Check(void)
//{
//	u8 temp;
//	temp=L_Single_Read(MPU_ADDRESS,WHO_AM_I);			  
//	if(temp==0X68)return 0;		  
//	else	
//	return 1;											 
//}


//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void L_MPU_Set_Gyro_Fsr(u8 fsr)
{
	L_Single_Write(MPU_ADDRESS,MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
void R_MPU_Set_Gyro_Fsr(u8 fsr)
{
	R_Single_Write(MPU_ADDRESS,MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}

//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g

void L_MPU_Set_Accel_Fsr(u8 fsr)
{
	L_Single_Write(MPU_ADDRESS,MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
void R_MPU_Set_Accel_Fsr(u8 fsr)
{
	R_Single_Write(MPU_ADDRESS,MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
//side: 1 Left side set ,0 Right side set
u8 MPU_Set_LPF(u16 lpf,u8 side)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	if(side==1)
	{
	  L_Single_Write(MPU_ADDRESS,MPU_CFG_REG,data);//�������ֵ�ͨ�˲��� 
	}
	else
	{
	  R_Single_Write(MPU_ADDRESS,MPU_CFG_REG,data);//�������ֵ�ͨ�˲��� 
	}
	return 0;
}


//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
//side: 1 Left side set ,0 Right side set
u8 MPU_Set_Rate(u16 rate,u8 side)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	L_Single_Write(MPU_ADDRESS,MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2,side);	//�Զ�����LPFΪ�����ʵ�һ��
}

////IIC����д
////addr:������ַ 
////reg:�Ĵ�����ַ
////len:д�볤��
////buf:������
////����ֵ:0,����
////    ����,�������
//u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
//{
//	u8 i; 
//    i2c_Start(); 
//	  i2c_SendByte((addr<<1)|0);//����������ַ+д����	
//	if(i2c_WaitAck())	//�ȴ�Ӧ��
//	{
//		i2c_Stop();		 
//		return 1;		
//	}
//    i2c_SendByte(reg);	//д�Ĵ�����ַ
//    i2c_WaitAck();		//�ȴ�Ӧ��
//	for(i=0;i<len;i++)
//	{
//		i2c_SendByte(buf[i]);	//��������
//		if(i2c_WaitAck())		//�ȴ�ACK
//		{
//			i2c_Stop();	 
//			return 1;		 
//		}		
//	}    
//    i2c_Stop();	 
//	return 0;	
//} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 L_MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	L_i2c_Start(); 
	L_i2c_SendByte((addr<<1)|0);//����������ַ+д����	
	if(L_i2c_WaitAck())	//�ȴ�Ӧ��
	{
		L_i2c_Stop();		 
		return 1;		
	}
    L_i2c_SendByte(reg);	//д�Ĵ�����ַ
    L_i2c_WaitAck();		//�ȴ�Ӧ��
    L_i2c_Start();
	  L_i2c_SendByte((addr<<1)|1);//����������ַ+������	
    L_i2c_WaitAck();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=L_i2c_ReadByte(0);//������,����nACK 
		else *buf=L_i2c_ReadByte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    L_i2c_Stop();	//����һ��ֹͣ���� 
	return 0;	
}

u8 R_MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	R_i2c_Start(); 
	R_i2c_SendByte((addr<<1)|0);//����������ַ+д����	
	if(R_i2c_WaitAck())	//�ȴ�Ӧ��
	{
		R_i2c_Stop();		 
		return 1;		
	}
    R_i2c_SendByte(reg);	//д�Ĵ�����ַ
    R_i2c_WaitAck();		//�ȴ�Ӧ��
    R_i2c_Start();
	  R_i2c_SendByte((addr<<1)|1);//����������ַ+������	
    R_i2c_WaitAck();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=R_i2c_ReadByte(0);//������,����nACK 
		else *buf=R_i2c_ReadByte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    R_i2c_Stop();	//����һ��ֹͣ���� 
	return 0;	
}

////IICдһ���ֽ� 
////reg:�Ĵ�����ַ
////data:����
////����ֵ:0,����
////    ����,�������
//u8 MPU_Write_Byte(u8 reg,u8 data) 				 
//{ 
//  i2c_Start(); 
//	i2c_SendByte(MPU_ADDRESS);//����������ַ+д����	
//	if(i2c_WaitAck())	//�ȴ�Ӧ��
//	{
//		i2c_Stop();		 
//		return 1;		
//	}
//  i2c_SendByte(reg);	//д�Ĵ�����ַ
//  i2c_WaitAck();		//�ȴ�Ӧ�� 
//	i2c_SendByte(data);//��������
//	if(i2c_WaitAck())	//�ȴ�ACK
//	{
//		i2c_Stop();	 
//		return 1;		 
//	}		 
//    i2c_Stop();	 
//	return 0;
//}
////IIC��һ���ֽ� 
////reg:�Ĵ�����ַ 
////����ֵ:����������
//u8 MPU_Read_Byte(u8 reg)
//{
//	u8 res;
//  i2c_Start(); 
//	i2c_SendByte(MPU_ADDRESS);//����������ַ+д����	
//	i2c_WaitAck();		//�ȴ�Ӧ�� 
//  i2c_SendByte(reg);	//д�Ĵ�����ַ
//  i2c_WaitAck();		//�ȴ�Ӧ��
//  i2c_Start();
//	i2c_SendByte(MPU_ADDRESS+1);//����������ַ+������	
//  i2c_WaitAck();		//�ȴ�Ӧ�� 
//	res=i2c_ReadByte(0);//��ȡ����,����nACK 
//  i2c_Stop();			//����һ��ֹͣ���� 
//	return res;		
//}

//��MPU605 ID
u8 L_ReadMPUID(void)
{
	u8 res;
	res=L_Single_Read(MPU_ADDRESS,WHO_AM_I);
	return res;
}

u8 R_ReadMPUID(void)
{
	u8 res;
	res=R_Single_Read(MPU_ADDRESS,WHO_AM_I);
	return res;
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
//side: 1 left side ,0 right side
short MPU_Get_Temperature(u8 side)
{
    u8 buf[2]; 
    short raw;
	float temp;
	if(side==1)
	{
	  L_MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
	}
	else
	{
	  R_MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 		
	}
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}

//short L_MPU_Get_Temperature(void)
//{
//    u8 buf[2]; 
//    short raw;
//	float temp;
//	L_MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
//    raw=((u16)buf[0]<<8)|buf[1];  
//    temp=36.53+((double)raw)/340;  
//    return temp*100;;
//}

//short R_MPU_Get_Temperature(void)
//{
//    u8 buf[2]; 
//    short raw;
//	float temp;
//	R_MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
//    raw=((u16)buf[0]<<8)|buf[1];  
//    temp=36.53+((double)raw)/340;  
//    return temp*100;;
//}

//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
//side: 1 left side, 0 right side
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az,u8 side)
{
    u8 buf[6],res;  
	if(side==1)
	{
	  res=L_MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	}
	else
	{
	  res=R_MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);		
	}
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

//u8 L_MPU_Get_Accelerometer(short *ax,short *ay,short *az)
//{
//    u8 buf[6],res;  
//	res=L_MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
//	if(res==0)
//	{
//		*ax=((u16)buf[0]<<8)|buf[1];  
//		*ay=((u16)buf[2]<<8)|buf[3];  
//		*az=((u16)buf[4]<<8)|buf[5];
//	} 	
//    return res;;
//}
//u8 R_MPU_Get_Accelerometer(short *ax,short *ay,short *az)
//{
//    u8 buf[6],res;  
//	res=R_MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
//	if(res==0)
//	{
//		*ax=((u16)buf[0]<<8)|buf[1];  
//		*ay=((u16)buf[2]<<8)|buf[3];  
//		*az=((u16)buf[4]<<8)|buf[5];
//	} 	
//    return res;;
//}

//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
//side:1 left side, 0 right side
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz,u8 side)
{
    u8 buf[6],res;  
	if(side==1)
	{
	  res=L_MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	}
	else 
	{
	  res=R_MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);		
	}
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//u8 L_MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
//{
//    u8 buf[6],res;  
//	res=L_MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
//	if(res==0)
//	{
//		*gx=((u16)buf[0]<<8)|buf[1];  
//		*gy=((u16)buf[2]<<8)|buf[3];  
//		*gz=((u16)buf[4]<<8)|buf[5];
//	} 	
//    return res;;
//}
//u8 R_MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
//{
//    u8 buf[6],res;  
//	res=R_MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
//	if(res==0)
//	{
//		*gx=((u16)buf[0]<<8)|buf[1];  
//		*gy=((u16)buf[2]<<8)|buf[3];  
//		*gz=((u16)buf[4]<<8)|buf[5];
//	} 	
//    return res;;
//}

void Init_MPU_6050(void)  				//��ʼ��MPU6050
{
	Delay_ms(100);
//	__nop();__nop();__nop();__nop();
	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X80);	//Reset MPU6050
	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X80);	//Reset MPU6050	
	Delay_ms(100);
//	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0x00);//�������״̬
	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0x00);//�������״̬	
//	Single_Write(MPU_ADDRESS,MPU_SAMPLE_RATE_REG,0x07);//�����ǲ����ʣ�1KHz
//	Single_Write(MPU_ADDRESS,MPU_CFG_REG,0x03);		
//	Single_Write(MPU_ADDRESS,MPU_GYRO_CFG_REG,0x00);//�������Լ켰������Χ������ֵ��0x1238(���Լ죬2000deg/s)
//	Single_Write(MPU_ADDRESS,MPU_ACCEL_CFG_REG,0x00); //���ü��ٶȴ�����������2Gģʽ�����Լ�  
	L_MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	L_MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50,1);						//���ò�����50Hz
	L_Single_Write(MPU_ADDRESS,MPU_INT_EN_REG,0X00);	//�ر������ж�
	L_Single_Write(MPU_ADDRESS,MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	L_Single_Write(MPU_ADDRESS,MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	L_Single_Write(MPU_ADDRESS,MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
	MPU_Set_Rate(100,1);						//���ò�����Ϊ50Hz
	
	R_MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	R_MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50,0);						//���ò�����50Hz
	R_Single_Write(MPU_ADDRESS,MPU_INT_EN_REG,0X00);	//�ر������ж�
	R_Single_Write(MPU_ADDRESS,MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	R_Single_Write(MPU_ADDRESS,MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	R_Single_Write(MPU_ADDRESS,MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
	MPU_Set_Rate(100,0);						//���ò�����Ϊ50Hz	
}

//void L_Init_MPU_6050(void)  				//��ʼ��MPU6050
//{
//	Delay_ms(100);
////	__nop();__nop();__nop();__nop();
//	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X80);	//Reset MPU6050
//	Delay_ms(100);
////	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0x00);//�������״̬
////	Single_Write(MPU_ADDRESS,MPU_SAMPLE_RATE_REG,0x07);//�����ǲ����ʣ�1KHz
////	Single_Write(MPU_ADDRESS,MPU_CFG_REG,0x03);		
////	Single_Write(MPU_ADDRESS,MPU_GYRO_CFG_REG,0x00);//�������Լ켰������Χ������ֵ��0x1238(���Լ죬2000deg/s)
////	Single_Write(MPU_ADDRESS,MPU_ACCEL_CFG_REG,0x00); //���ü��ٶȴ�����������2Gģʽ�����Լ�  
//	L_MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
//	L_MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
//	MPU_Set_Rate(50,1);						//���ò�����50Hz
//	L_Single_Write(MPU_ADDRESS,MPU_INT_EN_REG,0X00);	//�ر������ж�
//	L_Single_Write(MPU_ADDRESS,MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
//	L_Single_Write(MPU_ADDRESS,MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
//	L_Single_Write(MPU_ADDRESS,MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
//	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
//	L_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
//	MPU_Set_Rate(100,1);						//���ò�����Ϊ50Hz
//}

//void R_Init_MPU_6050(void)  				//��ʼ��MPU6050
//{
//	Delay_ms(100);
////	__nop();__nop();__nop();__nop();
//	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X80);	//Reset MPU6050
//	Delay_ms(100);
////	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
//	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0x00);//�������״̬
////	Single_Write(MPU_ADDRESS,MPU_SAMPLE_RATE_REG,0x07);//�����ǲ����ʣ�1KHz
////	Single_Write(MPU_ADDRESS,MPU_CFG_REG,0x03);		
////	Single_Write(MPU_ADDRESS,MPU_GYRO_CFG_REG,0x00);//�������Լ켰������Χ������ֵ��0x1238(���Լ죬2000deg/s)
////	Single_Write(MPU_ADDRESS,MPU_ACCEL_CFG_REG,0x00); //���ü��ٶȴ�����������2Gģʽ�����Լ�  
//	R_MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
//	R_MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
//	MPU_Set_Rate(50,0);						//���ò�����50Hz
//	R_Single_Write(MPU_ADDRESS,MPU_INT_EN_REG,0X00);	//�ر������ж�
//	R_Single_Write(MPU_ADDRESS,MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
//	R_Single_Write(MPU_ADDRESS,MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
//	R_Single_Write(MPU_ADDRESS,MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
//	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
//	R_Single_Write(MPU_ADDRESS,MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
//	MPU_Set_Rate(100,0);						//���ò�����Ϊ50Hz
//}


