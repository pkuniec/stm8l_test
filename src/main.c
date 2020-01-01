#include <stdlib.h>
#include "stm8l15x.h"
#include "stm8l_it.h"
#include "lcd.h"
#include "rtc.h"

volatile uint8_t flag;

void setup(void) {
	// CLK
	//CLK->CKDIVR = 0;

	// LSI
	CLK->ECKCR = CLK_ECKCR_LSEON;
	while( !(CLK->ECKCR & CLK_ECKCR_LSERDY) );
	
	// PE7 - LED green, PC7 - LED blue
	// GPIO
	GPIOE->DDR = 0x80;
	GPIOE->CR1 = 0x80;

	GPIOC->DDR = 0x80;
	GPIOC->CR1 = 0x80;

	// TIM4
	CLK->PCKENR1 = CLK_PCKENR1_TIM4;
	TIM4->PSCR = 0x05; // 64
	TIM4->ARR = 130;
	TIM4->IER = TIM4_IER_UIE;
	TIM4->CR1 = TIM4_CR1_CEN;
}




int main(void) {
	
	uint8_t lcd_digit[6];
	uint8_t tmp;

	setup();
	lcd_setup();
	LCD_ContrastConfig(0x08);
	SetBit(GPIOC->ODR, 7);

	enableInterrupts();

    while( 1 ) {
		if (flag) {
			flag = 0;
			ChgBit(GPIOE->ODR, 7);
			ChgBit(GPIOC->ODR, 7);

			tmp = RTC->TR3;
			lcd_digit[0] = (tmp>>4) + '0';
			lcd_digit[1] = (tmp & 0xCF) + '0';

			tmp = RTC->TR2;
			lcd_digit[2] = (tmp>>4) + '0';
			lcd_digit[3] = (tmp & 0x0F) + '0';

			tmp = RTC->TR1;
			lcd_digit[4] = (tmp>>4) + '0';
			lcd_digit[5] = (tmp & 0x0F) + '0';

			LCD_GLASS_WriteChar(&lcd_digit[0], 0, 0, 0);
			LCD_GLASS_WriteChar(&lcd_digit[1], 0, 1, 1);
			LCD_GLASS_WriteChar(&lcd_digit[2], 0, 0, 2);
			LCD_GLASS_WriteChar(&lcd_digit[3], 0, 1, 3);
			LCD_GLASS_WriteChar(&lcd_digit[4], 0, 0, 4);
			LCD_GLASS_WriteChar(&lcd_digit[5], 0, 0, 5);
		}
    }
}