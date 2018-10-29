//IIC ��ʼ�ź� 
void IIC_Start(void) 
{ 
  SDA_OUT();						//sda ���������Ϊ��� 
  SDA=1;             
  delay_us(4); 
  SCL=1; 
  delay_us(4); 
  SDA=0;								//��������   
  delay_us(4); 
  SCL=0;								//ǯס I2C ���ߣ�׼�����ͻ�������� 
  delay_us(4);  
  }       
//���� IIC ֹͣ�ź� 
���컨��һ��Сʱд��mpu6050 I/0ģ�� i2c�ĵײ���������Կ��������Ѿ��ɹ�����mpu6050����Ϊ�ҵ����ϵ������������İ��ӡ�����Ӳ�������ԭ�ӵĲ�һ����ע���Լ��޸ġ�

#define	MPU6050_Addr   0xD0	 //����������IIC�����еĴӵ�ַ,����ALT ADDRESS��ַ���Ų�ͬ�޸� //����ע���ˣ�����i2c������ַ��7bit ����8bit����ģ��i2c����7bit���������0xd0 ����A0�����ǽӵء����Ƕ���who am I �Ĵ�����������0x68. bin���뷽����ѡ�
//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define SMPLRT_DIV      0x19    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define CONFIG          0x1A    //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define GYRO_CONFIG     0x1B    //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define ACCEL_CONFIG    0x1C    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define ACCEL_XOUT_H    0x3B
#define ACCEL_XOUT_L    0x3C
#define ACCEL_YOUT_H    0x3D
#define ACCEL_YOUT_L    0x3E
#define ACCEL_ZOUT_H    0x3F
#define ACCEL_ZOUT_L    0x40
#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42
#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44    
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48
#define PWR_MGMT_1      0x6B    //��Դ��������ֵ��0x00(��������)
#define WHO_AM_I        0x75    //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)

void MPU6050_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : I2C_Start 
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	Start
****************************************************************************** */
bool MPU6050_I2C_Start(void)
{
	MPU6050_SDA_H;
	MPU6050_SCL_H;
	delay_us(4);
	if(!MPU6050_SDA_read)return FALSE;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	MPU6050_SDA_L;
	delay_us(4);
	if(MPU6050_SDA_read) return FALSE;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	MPU6050_SDA_L;
	delay_us(4);
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MPU6050_I2C_Stop(void)
{
	MPU6050_SCL_L;
	delay_us(4);
	MPU6050_SDA_L;
	delay_us(4);
	MPU6050_SCL_H;
	delay_us(4);
	MPU6050_SDA_H;
	delay_us(4);
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MPU6050_I2C_Ack(void)
{	
	MPU6050_SCL_L;
	delay_us(1);
	MPU6050_SDA_L;
	delay_us(1);
	MPU6050_SCL_H;
	delay_us(1);
	MPU6050_SCL_L;
	delay_us(1);
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void MPU6050_I2C_NoAck(void)
{	
	MPU6050_SCL_L;
	delay_us(1);
	MPU6050_SDA_H;
	delay_us(1);
	MPU6050_SCL_H;
	delay_us(1);
	MPU6050_SCL_L;
	delay_us(1);
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	Reserive Slave Acknowledge Single
****************************************************************************** */
bool MPU6050_I2C_WaitAck(void) 	//����Ϊ:=1��ACK,=0��ACK
{
	MPU6050_SCL_L;
	delay_us(1);
	MPU6050_SDA_H;			
	delay_us(1);
	MPU6050_SCL_H;
	delay_us(1);
	if(MPU6050_SDA_read)
	{
      MPU6050_SCL_L;
	 delay_us(1);
      return FALSE;
	}
	MPU6050_SCL_L;
	delay_us(1);
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void MPU6050_I2C_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
    while(i--)
    {
        MPU6050_SCL_L;
        delay_us(1);
      if(SendByte&0x80)
        MPU6050_SDA_H;  
      else 
        MPU6050_SDA_L;   
        SendByte<<=1;
        delay_us(1);
		MPU6050_SCL_H;
        delay_us(1);
    }
    MPU6050_SCL_L;
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char MPU6050_I2C_RadeByte(void)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    MPU6050_SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      MPU6050_SCL_L;
      delay_us(1);
	 MPU6050_SCL_H;
      delay_us(1);	
      if(MPU6050_SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    MPU6050_SCL_L;
    return ReceiveByte;
}

//mpu6050 api
//��ʼ��MPU6050��������Ҫ��ο�pdf�����޸�************************
void Init_MPU6050(void)
{
   Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x00);   //
   Single_Write(MPU6050_Addr,SMPLRT_DIV, 0x07);    //
   Single_Write(MPU6050_Addr,CONFIG,0x03);			//���������=1khz/1+7��smpl����div��=125hz
   Single_Write(MPU6050_Addr,GYRO_CONFIG, 0x00);    //��250��
   Single_Write(MPU6050_Addr,ACCEL_CONFIG, 0x00 );  //
  
}
//���ֽ�д��*******************************************

bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		    //void
{
  	if(!MPU6050_I2C_Start())return FALSE;
    MPU6050_I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!MPU6050_I2C_WaitAck()){MPU6050_I2C_Stop(); return FALSE;}
    MPU6050_I2C_SendByte(REG_Address );   //���õ���ʼ��ַ      
    MPU6050_I2C_WaitAck();	
    MPU6050_I2C_SendByte(REG_data);
    MPU6050_I2C_WaitAck();   
    MPU6050_I2C_Stop(); 
    delay_ms(5);
    return TRUE;
}

//���ֽڶ�ȡ*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!MPU6050_I2C_Start())return FALSE;
    MPU6050_I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!MPU6050_I2C_WaitAck()){MPU6050_I2C_Stop(); return FALSE;}
    MPU6050_I2C_SendByte((u8) REG_Address);   //���õ���ʼ��ַ      
    MPU6050_I2C_WaitAck();
    MPU6050_I2C_Start();
    MPU6050_I2C_SendByte(SlaveAddress+1);
    MPU6050_I2C_WaitAck();

	REG_data= MPU6050_I2C_RadeByte();
    MPU6050_I2C_NoAck();
    MPU6050_I2C_Stop();
    //return TRUE;
	return REG_data;

}//���MPU6050�Ƿ�����
//����6050���who am I �Ĵ��� 
//����1:���ʧ��
//����0:���ɹ�
u8 MPU6050_Check(void)
{
	u8 temp;
	temp=Single_Read(MPU6050_Addr,WHO_AM_I);			  
	if(temp==0X68)return 0;		  
	else	
	return 1;											 
}


