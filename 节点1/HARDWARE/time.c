#include "stm32f10x.h"
#include "led.h"
#include "time.h"


void TIM3_IRQHandler(void)
{

    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//是更新中断
    {
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIM2更新中断标志
    }  
		  				 	
}
//通用定时器2中断初始化
//这里时钟选择为APB1的2倍，而APB1为42M
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//通用定时器中断初始化
//这里始终选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
void TIM3_Int_Init(u16 arr,u16 psc)
{
		NVIC_InitTypeDef NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//TIM7时钟使能

		//定时器TIM2初始化
		TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM7中断,允许更新中断

		TIM_Cmd(TIM3,ENABLE);//开启定时器2

		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}
    /*
    	}*/
