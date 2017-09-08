#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "led.h"
#include "time1.h"
int main()
{
	// u16 reclen;
	 //char date[5]={'s','1','2','m',0};
	 LED_Init();
	 delay_init();
	 uart_init(9600);
   usart2_init(9600);
	 TIM4_Int_Init(7200-1,999); //10khz  100ms
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 while(1)
	 {
     
	    if(USART2_RX_STA&0X8000)
			{
			   //reclen=USART2_RX_STA&0X7FFF;	//得到数据长度
         if(USART2_RX_BUF[0]=='c'&&USART2_RX_BUF[1]=='m')
				 {
				      if(USART2_RX_BUF[2]=='1')
							   GPIO_SetBits(GPIOB,GPIO_Pin_5);
							else if(USART2_RX_BUF[2]=='0')
								 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
				 }
				 USART2_RX_STA=0;
			}
//			if(flag_send==1)
//			{
//			   flag_send=0;
//				 usart2_write(date);
//				 printf("%s",date);
//			}
	 }		 
	
}

//int main()
//{
//	   u16 reclen,count=0;
//	   u16 i,flag=0;
//	   u16  a[100];
//	   delay_init();
//	   usart2_init(9600);
//	   uart_init(9600);
//	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//    while(1)
//		{
//		   if(USART2_RX_STA&0X8000)			//接收到一次数据了
//			{
//				reclen=USART2_RX_STA&0X7FFF;	//得到数据长度
//				//USART2_RX_BUF[reclen]=0;	 	//加入结束符
//				for(i=0;i<reclen;i++)
//				{
//				    u2_printf("%x ",USART2_RX_BUF[i]);
//					if(flag==1)
//					{
//					   a[count]=USART2_RX_BUF[i];
//						 
//						if(++count==2)
//							count=0,flag=0;
//					}
//					if(USART2_RX_BUF[i-1]==0x14&&USART2_RX_BUF[i]==0x11)
//					{
//					   flag=1;
//					}

//				}
//				u2_printf("\n");
//				u2_printf("\n");
//				u2_printf("%x %x\n",a[0],a[1]);
//				USART2_RX_STA=0;
//			}
//		}
//}


