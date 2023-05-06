#ifndef _BSP_PWM_H
#define _BSP_PWM_H


#include "gd32f4xx.h"
#include "systick.h"

#define BSP_PWM_RCU     RCU_GPIOA
#define BSP_PWM_PORT    GPIOA
#define BSP_PWM_PIN     GPIO_PIN_5
#define BSP_PWM_AF      GPIO_AF_1


#define BSP_PWM_TIMER_RCU  				RCU_TIMER1
#define BSP_PWM_TIMER      				TIMER1
#define BSP_PWM_CHANNEL  					TIMER_CH_0

void pwm_config(uint16_t pre,uint16_t per);
void pwm_breathing_lamp(void);

#endif
