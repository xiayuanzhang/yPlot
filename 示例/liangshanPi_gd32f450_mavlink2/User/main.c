/*!
    \file    main.c
    \brief   led spark with systick

    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
    \version 2020-09-30, V2.1.0, firmware for GD32F4xx
    \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "bsp_led.h"
#include "sys.h"
#include "bsp_usart.h"
#include "bsp_key.h"
#include "bsp_basic_timer.h"
#include "bsp_pwm.h"
#include "stdlib.h"
#include "string.h"

#include "mavlink.h"




void send_plotName(void);
void send_plot(void);

int main(void)
{

	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);  // 优先级分组
    systick_config();
	
	led_gpio_config();  // led初始化
    key_gpio_config(); // key初始化
	usart_gpio_config(256000);

	send_plotName();
    while(1) {

    //定义消息类型
   
		send_plot();
    }
}


void send_plotName(void)
{
	mavlink_plotname_t mplotName;
	mavlink_message_t msg;
	
	memcpy(mplotName.plotName0,"sin",sizeof("sin"));
	memcpy(mplotName.plotName1,"cos",sizeof("cos"));
	memcpy(mplotName.plotName2,"P",sizeof("P"));

	
	mavlink_msg_plotname_encode_chan (0,1,MAVLINK_COMM_0,&msg,&mplotName);
	
	uint8_t buf[512] = {0};
    uint16_t rlen = mavlink_msg_to_send_buffer(buf, &msg);
	usart_send_ndata(buf,rlen);
	
}
void send_plot(void)
{
	static float x = 0.00f * 3.1415f;
	
	mavlink_plot_t mplot;
	mavlink_message_t msg;
	
	mplot.plotNum = 12;
	mplot.plot[0] = sinf(x) * 10;
	mplot.plot[1] = cosf(x) * 10;
	mplot.plot[2] = (int)x % 10;
	mplot.plot[3] = sinf(x+0.1f) * 10;
	mplot.plot[4] = cosf(x+0.1f) * 10;
	mplot.plot[5] = (int)x % 10;
	mplot.plot[6] = sinf(x+0.2f) * 10;
	mplot.plot[7] = cosf(x+0.2f) * 10;
	mplot.plot[8] = (int)x % 10;
	mplot.plot[9] = sinf(x+0.3f) * 10;
	mplot.plot[10] = cosf(x+0.3f) * 10;
	mplot.plot[11] = (int)x % 10;
	
	x+=0.001f;
	
	mavlink_msg_plot_encode_chan (0,1,MAVLINK_COMM_0,&msg,&mplot);
	uint8_t buf[512] = {0};
    uint16_t rlen = mavlink_msg_to_send_buffer(buf, &msg);
	usart_send_ndata(buf,rlen);
}



mavlink_message_t msg;
mavlink_status_t status;
void USART0_IRQHandler(void)
{
	uint8_t ch;
	if(usart_interrupt_flag_get(BSP_USART,USART_INT_FLAG_RBNE) == SET)
	{
		ch = usart_data_receive(BSP_USART);
		//这里需要使用队列缓存串口数据,然后进行解析
		if(mavlink_parse_char(MAVLINK_COMM_0, ch, &msg, &status))
        {
            
        }
	}
}



