#include "beep.h"
#include "./SYSTEM/sys/sys.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitLed;//??GPIO_InitTypeDef??????
	
	__HAL_RCC_GPIOB_CLK_ENABLE();//??GPIOB???
	
	GPIO_InitLed.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitLed.Pin=GPIO_PIN_8;
	GPIO_InitLed.Speed=GPIO_SPEED_FREQ_HIGH;
	GPIO_InitLed.Pull=GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB,&GPIO_InitLed);
	
}
