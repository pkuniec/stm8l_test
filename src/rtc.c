#include <stdlib.h>
#include "stm8l15x.h"

void rtc_setup(void) {
    //CLK->CRTCR = 0x10; // div: 1, src: LSE
    //CLK->PCKENR2 |= CLK_PCKENR2_RTC;

    // Check init year value
    if ( !(RTC->ISR1 & RTC_ISR1_INITS) ) {

        // Disable write protect
        RTC->WPR = 0xCA;
        RTC->WPR = 0x53;

        // Init mode
        RTC->ISR1 = RTC_ISR1_INIT;
        while( !(RTC->ISR1 & RTC_ISR1_INITF) );

        // Set time

        // Set date

        // Exit init mode
        RTC->ISR1 = 0x00;
    }

}