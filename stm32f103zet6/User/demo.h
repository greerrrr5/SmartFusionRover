/**
 ****************************************************************************************************
 * @file        demo.h
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

#ifndef __DEMO_H
#define __DEMO_H

#include "stm32f1xx.h"

static void demo_show_ip(char *buf);
void OneNet_FillBuf(char *buf,uint8_t temperature,uint8_t humidity,uint16_t sunlight,uint32_t C02,uint32_t TVOC,uint16_t LPG);
void wifi_init(void);
void information_connection(uint8_t temperature,uint8_t humidity,uint16_t sunlight,uint32_t C02,uint32_t TVOC,uint16_t LPG);

#endif
