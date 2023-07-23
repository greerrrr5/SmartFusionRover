#ifndef __SHT30_H__
#define __SHT30_H__
#include "./SYSTEM/sys/sys.h"

#define IIC_SCL PFout(10)


//IO方向设置
#define IIC_SDAIN_Mode()  {GPIOF->CRH&=0XFFFF0FFF;GPIOF->CRH|=8<<12;}
#define IIC_SDAout_Mode() {GPIOF->CRH&=0XFFFF0FFF;GPIOF->CRH|=3<<12;}

//IO操作函数											   
#define	IIC_SDAout    PFout(11)//数据端口	PF11
#define	IIC_SDAin     PFin(11) //数据端口	PF11

//命令

#define BHAddWrite     0x46      //写地址
#define BHAddRead      0x47      //读地址
#define BHPowDown      0x00      //关闭模块
#define BHPowOn        0x01      //打开模块等待指令 
#define BHReset        0x07      //重置数据寄存器仅在BHpowOn模式下有效
#define BHModeH1       0x10      //高分辨率 模式1 单位 11X 测量时间 120ms 
#define BHModeH2       0x11      //高分辨率 模式2 单位 11X 测量时间 120ms 
#define BHModeL        0x13      //低分辨率 单位4lx 测量时间16ms  
#define BHSigModeH     0x20      //一次测量高分辨率模式1，然后转到powerdown模式
#define BHSigModeH2    0x21      //同上类似
#define BHSigModeL     0x23      //同上类似  



void bh_data_send(unsigned char command);
unsigned short bh_data_read(void);
void BH1750init(void);
#endif 
