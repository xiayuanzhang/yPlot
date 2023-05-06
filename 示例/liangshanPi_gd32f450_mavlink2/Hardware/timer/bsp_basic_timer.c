#include "bsp_basic_timer.h"
#include "bsp_led.h"
#include "stdio.h"


void basic_timer_config(uint16_t pre,uint16_t per)
{
	timer_parameter_struct timere_initpara;
	
	rcu_periph_clock_enable(BSP_TIMER_RCU);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	
	timer_deinit(BSP_TIMER);
	
	timere_initpara.prescaler = pre-1;                       
	timere_initpara.alignedmode = TIMER_COUNTER_EDGE;                      
	timere_initpara.counterdirection = TIMER_COUNTER_UP;                
	timere_initpara.clockdivision = TIMER_CKDIV_DIV1;                  
	timere_initpara.period = per-1;                          
	timere_initpara.repetitioncounter = 0; 
	
	timer_init(BSP_TIMER,&timere_initpara);
	
	
	nvic_irq_enable(BSP_TIMER_IRQ,3,2);
	
	timer_interrupt_enable(BSP_TIMER,TIMER_INT_UP);
	
	timer_enable(BSP_TIMER);
}


void BSP_TIMER_IRQHANDLER(void)
{
  if(timer_interrupt_flag_get(BSP_TIMER,TIMER_INT_FLAG_UP) == SET)
	{
		timer_interrupt_flag_clear(BSP_TIMER,TIMER_INT_FLAG_UP);
		/* Ö´ÐÐ¹¦ÄÜ */
		gpio_bit_toggle(PORT_LED2,PIN_LED2);
		printf("BSP_TIMER_IRQHANDLER!\r\n");
	}
}
