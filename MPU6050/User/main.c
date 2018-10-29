/*
**  ���ߣ�RandyChan
**  ��ϵ��154722299@qq.com
**  �޸����ڣ�2016.08.22
**  ˵��: ģ��I2C�ӿڶ�ȡMPU6050���ٶ�ԭʼ���ݣ�����X,Y,Z����ˮƽ��нǣ�
          ������Ƕȴ���45�ȣ�LED��.
					�ɶ�ȡ������ԭʼ���ݡ�
*/

/*

����
LED1  PA5
LED2  PA6

��MPU6050 
SDA   PA1
SCL   PA2

��MPU6050 
SDA   PA3
SCL   PA4

*/

#include "ALL_Includes.h"//���������ͷ�ļ�
//#include "anbt_dmp_fun.h"
//#include "anbt_i2c.h"
//#include "anbt_dmp_mpu6050.h"
//#include "anbt_dmp_driver.h"
//#include "mpu6050.h"
#include "USART1.h"
#include "MPU6050.h"
#include "math.h"

//#define q30  1073741824.0f

//void ALL_Config(void);

u8 Readbuf=0;

//u16 TemperH=0;
//u16 TemperL=0;
//u16 Temper=0;
//u16 accelxL=0;   //���ٶ�X���λ
//u16 accelxH=0;   //���ٶ�X���λ
//u16 accelyL=0;   //���ٶ�y���λ
//u16 accelyH=0;   //���ٶ�y���λ
//u16 accelzL=0;   //���ٶ�z���λ
//u16 accelzH=0;   //���ٶ�z���λ
//u16 gyroxL=0;    //������X���λ
//u16 gyroxH=0;    //������X���λ
//u16 gyroyL=0;    //������y���λ
//u16 gyroyH=0;    //������y���λ
//u16 gyrozL=0;    //������z���λ
//u16 gyrozH=0;    //������z���λ
short Laacx,Laacy,Laacz;		//���ٶȴ�����ԭʼ����
short Lgyrox,Lgyroy,Lgyroz;	//������ԭʼ����
short LTemper;     //�¶�ԭʼ����
short LangleX;     //X����ȻX��ĽǶ�
short LangleY;      //Y����ȻY��ĽǶ�
short LangleZ;       //Z����ȻZ��ĽǶ�
short Raacx,Raacy,Raacz;		//���ٶȴ�����ԭʼ����
short Rgyrox,Rgyroy,Rgyroz;	//������ԭʼ����
short RTemper;     //�¶�ԭʼ����
short RangleX;      //X����ȻX��ĽǶ�
short RangleY;       //Y����ȻY��ĽǶ�
short RangleZ;       //Z����ȻZ��ĽǶ�

u8 LEDbuf1=0;    //LED1��ʾ��־
u8 LEDbuf2=0;    //LED2��ʾ��־

//float YawR=0.00,RollR=0.00,PitchR=0.00;//ŷ����
//float YawL=0.00,RollL=0.00,PitchL=0.00;//ŷ����
//long quat[4];//��Ԫ���������


//�õ��Ƕ�
//x,y,z:x,y,z������������ٶȷ���(����Ҫ��λ,ֱ����ֵ����)
//dir:Ҫ��õĽǶ�.0,��Z��ĽǶ�;1,��X��ĽǶ�;2,��Y��ĽǶ�.
//����ֵ:�Ƕ�ֵ.��λ0.1��.
short MPU_Get_Angle(float x,float y,float z,u8 dir)
{
	float temp;
 	float res=0;
	switch(dir)
	{
		case 0://����ȻZ��ĽǶ�
 			temp=sqrt((x*x+y*y))/z;
 			res=atan(temp);
 			break;
		case 1://����ȻX��ĽǶ�
 			temp=x/sqrt((y*y+z*z));
 			res=atan(temp);
 			break;
 		case 2://����ȻY��ĽǶ�
 			temp=y/sqrt((x*x+z*z));
 			res=atan(temp);
 			break;
 	}
	return res*573.25;
}




int main(void)
{	

	//    Delay_Init(48);
		LED_Init();          //LED���ų�ʼ��
//		i2c_GPIO_Config();
	  USART1_Init(115200);	 //���ڳ�ʼ��
		MPU6050_Init();		//IIC��ʼ����MPU6050��ʼ��,����IO�ڳ�ʼ��
	
	
	  LEDbuf1=1;
	  LEDbuf2=0;
	
//  Readbuf=L_ReadMPUID();
	while(1)
	{
//			LED_ON();
			Delay_ms(10);
//			LED_OFF();
//			delay_ms(500);

			if(LEDbuf1==1)
			{
				LED_ON(1);
			}
			else
			{
				LED_OFF(1);
			}

			if(LEDbuf2==1)
			{
				LED_ON(2);
			}
			else
			{
				LED_OFF(2);
			}
		

//			 TemperH=(u16)Single_Read(MPU_ADDRESS,MPU_TEMP_OUTH_REG);
//			 TemperL=Single_Read(MPU_ADDRESS,MPU_TEMP_OUTL_REG);
//			 Temper=((TemperH<<8)|((u16)TemperL));
//			LTemper=MPU_Get_Temperature(1);   //���¶�����
//			RTemper=MPU_Get_Temperature(0);    //���¶�����


			MPU_Get_Accelerometer(&Laacx,&Laacy,&Laacz,1);	//�õ�����ٶȴ���������
			MPU_Get_Gyroscope(&Lgyrox,&Lgyroy,&Lgyroz,1);	//�õ�������������
      MPU_Get_Accelerometer(&Raacx,&Raacy,&Raacz,0);	//�õ��Ҽ��ٶȴ���������
			MPU_Get_Gyroscope(&Rgyrox,&Rgyroy,&Rgyroz,1);	//�õ�������������
			
			LangleZ=MPU_Get_Angle(Laacx,Laacy,Laacz,0);
			LangleX=MPU_Get_Angle(Laacx,Laacy,Laacz,1);
			LangleY=MPU_Get_Angle(Laacx,Laacy,Laacz,2);

			RangleZ=MPU_Get_Angle(Raacx,Raacy,Raacz,0);
			RangleX=MPU_Get_Angle(Raacx,Raacy,Raacz,1);
			RangleY=MPU_Get_Angle(Raacx,Raacy,Raacz,2);
			
			if((LangleX>450)|(LangleY>450)|(LangleZ>450))
			{
				LEDbuf1=1;
			}
			else
			{
				LEDbuf1=0;
			}
			if((RangleX>450)|(RangleY>450)|(RangleZ>450))
			{
				LEDbuf2=1;
			}
			else
			{
				LEDbuf2=0;
			}
			
			//���ٶ�X������
//			 accelxH=Single_Read(MPU_ADDRESS,MPU_ACCEL_XOUTH_REG);
//			 accelxL=Single_Read(MPU_ADDRESS,MPU_ACCEL_XOUTL_REG);
//			 accelx=((accelxH<<8)|accelxL);      
//			accelx=GetData(MPU_ACCEL_XOUTH_REG);
			//���ٶ�Y������
//			 accelyH=Single_Read(MPU_ADDRESS,MPU_ACCEL_YOUTH_REG);
//			 accelyL=Single_Read(MPU_ADDRESS,MPU_ACCEL_YOUTL_REG);
//			 accely=((accelyH<<8)|accelyL);
//			accely=GetData(MPU_ACCEL_YOUTH_REG);
			//���ٶ�Z������
//			 accelzH=Single_Read(MPU_ADDRESS,MPU_ACCEL_ZOUTH_REG);
//			 accelzL=Single_Read(MPU_ADDRESS,MPU_ACCEL_ZOUTL_REG);
//			 accelz=((accelzH<<8)|accelzL);			
//			accelz=GetData(MPU_ACCEL_ZOUTH_REG);
			
			 //������X������
//			 gyroxH=Single_Read(MPU_ADDRESS,MPU_GYRO_XOUTH_REG);
//			 gyroxL=Single_Read(MPU_ADDRESS,MPU_GYRO_XOUTL_REG);
//			 gyrox=((gyroxH<<8)|gyroxL);
//			 gyrox=GetData(MPU_GYRO_XOUTH_REG);
			 //������Y������
//			 gyroyH=Single_Read(MPU_ADDRESS,MPU_GYRO_YOUTH_REG);
//			 gyroyL=Single_Read(MPU_ADDRESS,MPU_GYRO_YOUTL_REG);
//			 gyroy=((gyroyH<<8)|gyroyL);
//			 gyroy=GetData(MPU_GYRO_YOUTH_REG);
       //������Z������
//			 gyrozH=Single_Read(MPU_ADDRESS,MPU_GYRO_ZOUTH_REG);
//			 gyrozL=Single_Read(MPU_ADDRESS,MPU_GYRO_ZOUTL_REG);
//			 gyroz=((gyrozH<<8)|gyrozL);
//       gyroz=GetData(MPU_GYRO_ZOUTH_REG);
			 
			 
//					dmp_read_fifoR(gyro, accel, quat, &sensor_timestamp, &sensors,&more);				
//					if(sensors&INV_WXYZ_QUAT)
//					 {					 
//						 q0=quat[0] / q30;
//						 q1=quat[1] / q30;
//						 q2=quat[2] / q30;
//						 q3=quat[3] / q30;
//						 PitchR = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
//						 RollR = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
//						 YawR = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
//					 }		
				 
//					dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);				
//					if(sensors&INV_WXYZ_QUAT)
//					 { 
//						 q0=quat[0] / q30;
//						 q1=quat[1] / q30;
//						 q2=quat[2] / q30;
//						 q3=quat[3] / q30;
//						 PitchL = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
//						 RollL = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
//						 YawL = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
//					 }		

	}
}




//#ifdef  USE_FULL_ASSERT

//void assert_failed(uint8_t* file, uint32_t line)
//{

//  while (1)
//  {
//  }
//}
//#endif



