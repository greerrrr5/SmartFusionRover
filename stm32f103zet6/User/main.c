/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266D模块原子云连接实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/DHT11/dht11.h"
#include "./BSP/GY-30/gy-30.h"
#include "./BSP/SGP30/sgp30.h"
#include "./BSP/MQ/adc.h"
#include "./BSP/MQ/beep.h"
#include "demo.h"


/**
 * @brief       显示实验信息
 * @param       无
 * @retval      无
 */
void show_mesg(void)
{
    /* LCD显示实验信息 */
    lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
    lcd_show_string(10, 47, 220, 24, 24, "ATK-MW8266D", RED);
    lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(10, 97, 220, 16, 16, "KEY0: test key", BLUE);
    lcd_show_string(10,118, 220, 16, 16, "KEY1: switch atkcld mode", BLUE);
    
//    /* 串口输出实验信息 */
//    printf("\n");
//    printf("********************************\r\n");
//    printf("STM32\r\n");
//    printf("ATK-MW8266D\r\n");
//    printf("ATOM@ALIENTEK\r\n");
//    printf("KEY0: test key\r\n");
//    printf("KEY1: switch atkcld mode\r\n");
//    printf("********************************\r\n");
//    printf("\r\n");
}

int main(void)
{   
	  /*温度湿度数据*/
    uint8_t temperature;  	    
	  uint8_t humidity;
	  uint16_t sunlight;
	  uint32_t sgp30_dat;
	  uint32_t CO2=0;
	  uint32_t TVOC=0;
	  uint16_t LPG=0;
	
	  /*状态变量*/
	  uint8_t t=0;
	  uint8_t is_unvarnished=0;
	
	  /*初始化函数*/
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    led_init();                         /* 初始化LED */
    key_init();                         /* 初始化按键 */
    lcd_init();                         /* 初始化LCD */
    show_mesg();                        /* 显示实验信息 */
	  MY_ADC_Init();
		
	  /*连接onenet*/
	  wifi_init();
	  
		/*传感器初始化*/
    BH1750init();
		SGP30_Init();
		
	  while(DHT11_Init())	//DHT11初始化	
	  {
		  lcd_show_string(30,130,200,16,16,"DHT11 Error",BLUE);
		  delay_ms(200);
	  }
		
		/*数据传输与显示*/
	  while(1)
		{ 
			if(t%10==0)
			{
				/*读取数据*/
				sunlight=bh_data_read();
				DHT11_Read_Data(&temperature,&humidity);
				
				//SGP30模块开机需要一定时间初始化，在初始化阶段读取的CO2浓度为400ppm，TVOC为0ppd且恒定不变，因此上电后每隔一段时间读取一次
	      //SGP30模块的值，如果CO2浓度为400ppm，TVOC为0ppd，发送“正在检测中...”，直到SGP30模块初始化完成。
	      //初始化完成后刚开始读出数据会波动比较大，属于正常现象，一段时间后会逐渐趋于稳定。
	      //气体类传感器比较容易受环境影响，测量数据出现波动是正常的，可自行添加滤波函数。
				while(CO2==00&&TVOC==0)
	      {
		      SGP30_Write(0x20,0x08);
		      sgp30_dat=SGP30_Read();//读取SGP30的值
		      CO2=(sgp30_dat&0xffff0000) >> 16;//取出CO2浓度值
		      TVOC=sgp30_dat&0x0000ffff;			 //取出TVOC值
					delay_ms(500);
	      }
				SGP30_Write(0x20,0x08);
		    sgp30_dat=SGP30_Read();          //读取SGP30的值
		    CO2=(sgp30_dat&0xffff0000)>>16;  //取出CO2浓度值
		    TVOC=sgp30_dat&0x0000ffff;       //取出TVOC值
				LPG=600;                //取出LPG值
				//uint16_t ppm;
				//ppm=Get_Adc_Average(ADC_CHANNEL_4,20);
				//printf("%d\r\n",ppm);
				/*数据显示*/
				lcd_show_string(30,150,200,16,16,"Temp:  C",BLUE);	 
 	      lcd_show_string(30,170,200,16,16,"Humi:  %",BLUE);
				lcd_show_string(30,190,200,18,16,"Sun:   Lux",BLUE);
				lcd_show_string(30,210,200,18,16,"CO2:   ppm",BLUE);
				lcd_show_string(30,230,200,18,16,"TVOC:   ppd",BLUE);
				lcd_show_string(30,250,200,18,16,"LPG:   ppm",BLUE);
				
				
				lcd_show_num(30+40,150,temperature,2,16,BLUE);		//显示温度	   		   
			  lcd_show_num(30+40,170,humidity,2,16,BLUE);			  //显示湿度
        lcd_show_num(30+40-10,190,sunlight,3,16,BLUE);		//显示光照强度
        lcd_show_num(30+40-10,210,CO2,3,16,BLUE);         //显示CO2浓度
				lcd_show_num(30+40,230,TVOC,3,16,BLUE);           //显示TVOC浓度
        lcd_show_num(30+40-10,250,LPG,3,16,BLUE);         //显示LPG浓度
				information_connection(temperature,humidity,sunlight,CO2,TVOC,LPG);
			}
			delay_ms(10);
			t++;
			if(t==20)
			{
				t=0;
				LED0_TOGGLE();
			}
		}
}
