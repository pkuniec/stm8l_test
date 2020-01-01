#include <stdlib.h>
#include "stm8l15x.h"
#include "stm8l_it.h"

// Sec timer
void tim4_overflow(void) __interrupt (IT_TIM4_OVF) {
	static uint8_t cnt = 250;
	TIM4->SR1 &= ~TIM4_SR1_UIF;

	if ( !cnt-- ) {
		cnt = 250;
		flag = 1;
	}
}