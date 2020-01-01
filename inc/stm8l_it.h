#ifndef STM8S_IT__H
#define STM8S_IT__H

/* Interrupt numbers */
#define IT_FLASH			1
#define IT_DMA1_01			2
#define IT_DMA1_23			3
#define IT_RTC				4
#define IT_EXTI_EFPDV		5
#define IT_EXTI_BG			6
#define IT_EXTI_DH			7
#define IT_EXTI0			8
#define IT_EXTI1			9
#define IT_EXTI2			10
#define IT_EXTI3			11
#define IT_EXTI4			12
#define IT_EXTI5			13
#define IT_EXTI6			14
#define IT_EXTI7			15
#define IT_LCD				16
#define IT_CLK_TIM1_DAC		17
#define IT_COMP_ADC1		18
#define IT_TIM2_OVF			19
#define IT_TIM2_CMP			20
#define IT_TIM3_OVF			21
#define IT_TIM3_CMP			22
#define IT_TIM1_OVF			23
#define IT_TIM1_CMP			24
#define IT_TIM4_OVF			25
#define IT_SPI				26
#define IT_UART1_TX			27
#define IT_UART1_RX			28
#define IT_I2C				29


extern volatile uint8_t flag;

void tim4_overflow(void) __interrupt (IT_TIM4_OVF);


#endif
