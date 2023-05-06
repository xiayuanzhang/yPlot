#include "bsp_key.h"
#include "sys.h"
#include "bsp_led.h"
#include "stdio.h"

void key_gpio_config(void)
{
	/* 开启时钟 */
	rcu_periph_clock_enable(BSP_KEY_RCU);
	rcu_periph_clock_enable(RCU_SYSCFG);  
	
	/* 配置GPIO的模式 */
	gpio_mode_set(BSP_KEY_PORT,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN,BSP_KEY_PIN);
	
	nvic_irq_enable(BSP_KEY_EXTI_IRQN,3U,3U);
	syscfg_exti_line_config(BSP_KEY_EXTI_PORT_SOURCE,BSP_KEY_EXTI_PIN_SOURCE);
	
	
	exti_init(BSP_KEY_EXTI_LINE,EXTI_INTERRUPT,EXTI_TRIG_BOTH);
	exti_interrupt_enable(BSP_KEY_EXTI_LINE);
	exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
}


void BSP_KEY_EXTI_IRQHANDLER(void)
{
  if(exti_interrupt_flag_get(BSP_KEY_EXTI_LINE) == SET)
	{
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET)
		{
			 /* 按键按下操作的功能 */
			gpio_bit_toggle(PORT_LED2,PIN_LED2);
			printf("key press!\r\n");
		}else{
			/* 按键松开操作的功能 */
			printf("key release!\r\n");
		}
	  exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
	}
}


void key_scan(void)
{
	/* 获取按键引脚的电平状态 */
	if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET)
	{
		delay_1ms(20);
		if(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET)
		{
			/* 执行对应的功能 */
			gpio_bit_toggle(PORT_LED2,PIN_LED2);
			printf("key press!\r\n");
			while(gpio_input_bit_get(BSP_KEY_PORT,BSP_KEY_PIN) == SET);  // 检测按键松开
			printf("key release!\r\n");
		}
	}
}
