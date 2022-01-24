#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 


void usart_init(u32 bound);
u8 usart_get_data(char *cmd,float *d1,float *d2,float *d3);
void usart_senddatas(USART_TypeDef* USARTx,u8* addr,int size);
#endif


