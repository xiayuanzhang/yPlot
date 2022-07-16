#include "sys.h"
#include "usart.h"	
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 

//初始化IO 串口1 
//bound:波特率
void usart_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	
}

char usart_readbuff[30] = {0}; //串口接受缓存数组
u8 usart_readok = 0; //一帧数据处理标志
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 temp;
	static u8 count = 0;  // 接收数组控制变量
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //判断是否为接收中断
	{
		temp = USART_ReceiveData(USART1);	//读取接收到的数据,并清除中断标志
		if(temp == '#' && usart_readok == 0) 
		{
			usart_readbuff[count] = '#';
			usart_readok = 1;
			count = 0;
		}
		else if(usart_readok==0)
		{
			usart_readbuff[count] = temp; //保存接收到的数据到接收缓存数组
			count++; //数组下标切换
			if(count >= 30) // 防止数据越界
				count = 0;
		}
	}
}


 

u8 usart_get_data(char *cmd,float *d1,float *d2,float *d3)
{
	u8 flag = 0;
	if(usart_readok == 1)
	{
		if(sscanf(usart_readbuff,"%3s=%f,%f,%f#",
											cmd,d1,d2,d3)==4)
		{
			flag = 1;
		}
		//清除接收完成标志
		memset(usart_readbuff,0,sizeof(usart_readbuff));
		usart_readok = 0;
	}
	return flag;
}


void usart_senddatas(USART_TypeDef* USARTx,u8* addr,int size)
{
	while(size--) //判断数据发送完没有
	{
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);//等待上一个byte的数据发送结束。
		USART_SendData(USARTx,*addr);//调用STM32标准库函数发送数据
		addr++; //地址偏移
	}
}



