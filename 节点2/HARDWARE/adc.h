#ifndef __adc_H
#define __adc_H	
#include "stm32f10x.h"
#include "delay.h"
void Adc_Init(void);
u16 Get_Adc(u8 ch,u8 sequence); 
u16 Get_Ave_ADC(u8 ch,u8 sequence,u8 times);
#endif
