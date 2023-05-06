#include "bsp_pwm.h"


static void pwm_gpio_config(void)
{
	  /* 使能时钟 */
	rcu_periph_clock_enable(BSP_PWM_RCU);
	/* 配置GPIO的模式 */
	gpio_mode_set(BSP_PWM_PORT,GPIO_MODE_AF,GPIO_PUPD_NONE,BSP_PWM_PIN);
	/* 配置GPIO的输出 */
	gpio_output_options_set(BSP_PWM_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,BSP_PWM_PIN);
	gpio_af_set(BSP_PWM_PORT,BSP_PWM_AF,BSP_PWM_PIN);	
}


void pwm_config(uint16_t pre,uint16_t per)
{
	timer_parameter_struct timere_initpara;
	timer_oc_parameter_struct timer_ocintpara;
	
	pwm_gpio_config();
	
	rcu_periph_clock_enable(BSP_PWM_TIMER_RCU);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	
	timer_deinit(BSP_PWM_TIMER);
	timere_initpara.prescaler = pre-1;                       
	timere_initpara.alignedmode = TIMER_COUNTER_EDGE;                      
	timere_initpara.counterdirection = TIMER_COUNTER_UP;                
	timere_initpara.clockdivision = TIMER_CKDIV_DIV1;                  
	timere_initpara.period = per-1;                          
	timere_initpara.repetitioncounter = 0; 
	timer_init(BSP_PWM_TIMER,&timere_initpara);
	
	/* 输出结构体 */
	timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_channel_output_config(BSP_PWM_TIMER,BSP_PWM_CHANNEL,&timer_ocintpara);

	timer_channel_output_pulse_value_config(BSP_PWM_TIMER,BSP_PWM_CHANNEL,0);
	timer_channel_output_mode_config(BSP_PWM_TIMER,BSP_PWM_CHANNEL,TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(BSP_PWM_TIMER,BSP_PWM_CHANNEL,TIMER_OC_SHADOW_DISABLE);
	
	/* 只有高级定时器使用 */
//	timer_primary_output_config(TIMER0,ENABLE);
	
	timer_auto_reload_shadow_enable(BSP_PWM_TIMER);
	
	timer_enable(BSP_PWM_TIMER);
}

/* 呼吸灯 */
void pwm_breathing_lamp(void)
{
	static uint8_t direct = 0; // 方向
	static uint16_t value = 0; // 
	
	if(direct == 0){ // 逐渐变亮 
		value += 300;
		if(value > 10000)		
		   direct = 1;
	}else{ // 逐渐变暗
	  value -= 300;
		if(value <= 0)
			direct = 0;
	}
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER,BSP_PWM_CHANNEL,value);
	delay_1ms(50);
}




