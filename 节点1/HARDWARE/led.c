#include "led.h"
#include "stm32f10x.h"
//#define KEY GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
void LED_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_Init(GPIOB, &GPIO_InitStructure);		
}
 
