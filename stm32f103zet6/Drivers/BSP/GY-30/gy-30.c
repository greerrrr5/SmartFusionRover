#include "./BSP/GY-30/gy-30.h"
#include "./SYSTEM/delay/delay.h"

/*********IIC初始化************
**硬件接口：IIC_SCL -- PF10
**					IIC_SDA -- PF11
**
**
*******************************/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
  __HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟
	
  GPIO_Initure.Pin=GPIO_PIN_10;           //PF10
  GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
  GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
  GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
  HAL_GPIO_Init(GPIOF,&GPIO_Initure);     //初始化
}
//发送起始信号
void IIC_Start(void)
{
	IIC_SDAout_Mode();//输出模式
	IIC_SCL=1;
	IIC_SDAout=1;
	delay_us(2);
	IIC_SDAout=0;
	
	IIC_SCL=0;//方便后续数据收发
}
//停止信号
void IIC_Stop(void)
{
	IIC_SDAout_Mode();//输出模式
	IIC_SCL=0;
	IIC_SDAout=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SDAout=1;
}
/***********发送应答信号**************************
**
**形参：u8 ack -- 0应答，1非应答
**
***************************************************/
void IIC_SendAck(uint8_t ack)
{
	IIC_SDAout_Mode();//输出模式	
	IIC_SCL=0;//告诉从机，主机开始发送数据
	IIC_SDAout=ack&0x01;
	delay_us(2);
	IIC_SCL=1;//告诉从机，主机数据发送完成
	//方便下一次数据收发
	delay_us(2);
	IIC_SCL=0;
}
//获取应答信号
uint8_t IIC_Wait_Ack(void)
{
	uint8_t cnt=0;
	IIC_SDAIN_Mode();//配置为输入模式
	IIC_SDAout=1;	
	IIC_SCL=0;//告诉从机，主机需要获取数据
	delay_us(2);
	IIC_SCL=1;//从机数据发送完成，主机开始读取数据
	while(IIC_SDAin)
	{
		cnt++;
		delay_us(1);
		if(cnt>=100)return 1;
	}
	delay_us(2);
	IIC_SCL=0;//方便下一次数据收发
	return 0;
}
//发送一个字节数据
void IIC_Send_Byte(uint8_t data)
{
	uint8_t i=0;
	IIC_SDAout_Mode();//输出模式
	for(i=0;i<8;i++)
	{
		IIC_SCL=0;//告诉从机，主机开始发送数据
		if(data&0x80)IIC_SDAout=1;
		else IIC_SDAout=0;
		delay_us(2);
		IIC_SCL=1;//主机数据发送完成
		data<<=1;
		delay_us(2);
	}
	IIC_SCL=0;//方便下一次数据收发
}
//读取一个字节数据
uint8_t IIC_Read_Byte(void)
{
	uint8_t i=0;
	uint8_t data=0;
	IIC_SDAIN_Mode();//配置为输入模式
	for(i=0;i<8;i++)
	{
		IIC_SCL=0;//告诉从机，主机需要获取数据
		delay_us(2);
		IIC_SCL=1;//开始读取数据
		data<<=1;//默认收到0
		if(IIC_SDAin)data|=0x01;
		delay_us(2);
	}
	IIC_SCL=0;
	return data;
}

void bh_data_send(uint8_t command)  
{  
    do{  
    IIC_Start();                      //iic开始
    IIC_Send_Byte(BHAddWrite);       //写地址  
    }while(IIC_Wait_Ack());           //等待响应 
    IIC_Send_Byte(command);          //发送命令  
    IIC_Wait_Ack();                   //等待响应 
    IIC_Stop();                       //iic停止  
}   


uint16_t bh_data_read(void)  
{  
    uint16_t buf;  
    IIC_Start();                       //iic开始  
    IIC_Send_Byte(BHAddRead);         //发送读地址
    IIC_Wait_Ack();                     //等待响应  
    buf=IIC_Read_Byte();              //读取数据  
		IIC_SendAck(0);
    buf=buf<<8;                        //读取并保存高八位数据
    buf+=0x00ff&IIC_Read_Byte();      //读取并保存第八位数据
		IIC_SendAck(1);
    IIC_Stop();                        //发送停止信号
    return buf;   
}  

void BH1750init(void)
{
	IIC_Init();//GPIO初始化
	bh_data_send(BHPowOn);    //发送启动信号
	bh_data_send(BHReset);    //清除寄存器  
  bh_data_send(BHModeH1);   //设置为模式2
  delay_ms(180);            //最高延时180ms
}
