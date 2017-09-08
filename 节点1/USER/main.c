#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "time.h"
#include "led.h"
#include "usart2.h"
#include "time1.h"
int main()
{
	
	char date[6]={'d','a','1','2','m',0};
	delay_init();
  usart2_init(9600);
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM4_Int_Init(1000-1,7200-1);//100MS 
	while(1)
	{
//			 if(KEY==0)
//					GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//			 else if(KEY==1)  
//			    GPIO_SetBits(GPIOB,GPIO_Pin_5);
			if(flag_send==1)
			{
			   flag_send=0;
				 usart2_write(date);
				 //printf("%s",date);
			}
	}

}

