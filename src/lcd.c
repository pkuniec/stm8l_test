#include <stdlib.h>
#include "stm8l15x.h"

const uint16_t CharMap[] = {
    /* 0      1      2      3      4      5      6      7      8      9  */
    0x5F00,0x4200,0xF500,0x6700,0xEa00,0xAF00,0xBF00,0x04600,0xFF00,0xEF00,
    /*  :     -     .      *                             */
    0x0044,0xa000,0x0002,0x80dd, 0x0000, 0x0000, 0x0000,
    /* A      B      C      D      E      F      G      H      I  */
    0xFE00,0x6714,0x1d00,0x4714,0x9d00,0x9c00,0x3f00,0xfa00,0x0011,
    /* J      K      L      M      N      O      P      Q      R  */
    0x5300,0x9844,0x1900,0x5a42,0x5a06,0x5f00,0xFC00,0x5F04,0xFC04,
    /* S      T      U      V      W      X      Y      Z  */
    0xAF00,0x0414,0x5b00,0x18c0,0x5a84,0x00c9,0x0058,0x05c0
};



void lcd_setup(void) {

    // LCD + RTC
    //CLK->CRTCR = 0xE2; // div: 64, src: HIS
    CLK->CRTCR = 0x10; // div: 1, src: LSE
    CLK->PCKENR2 = CLK_PCKENR2_LCD | CLK_PCKENR2_RTC;

	LCD->FRQ = 0x0F;
	LCD->PM[0] = 0xFF;
	LCD->PM[1] = 0xFF;
	LCD->PM[2] = 0xFF;
	LCD->CR1 = 0x06;
	LCD->CR2 = 0x28;
	LCD->CR3 = LCD_CR3_LCDEN;
}


void LCD_ContrastConfig(uint8_t LCD_Contrast) {
    LCD->CR2 &= (uint8_t)(~LCD_CR2_CC); /* Clear the contrast bits  */
    LCD->CR2 |= LCD_Contrast; /* Select the maximum voltage value Vlcd */
}


void LCD_GLASS_Clear(void) {
    uint8_t counter;
    for (counter = 0; counter < 14; counter++) {
        LCD->RAM[counter] = LCD_RAM_RESET_VALUE;
    }
}

uint16_t LCD_Conv_Char_Seg(uint8_t* c, uint8_t point, uint8_t column) {
	uint16_t ch = 0 ;

    if ( (*c > 0x2F) && (*c < 0x5A) ) {
        ch = CharMap[*c - '0'];
    }

    if (column) {
        ch |= 0x0020;
    }

    if (point) {
        ch |= 0x0002;
    }

    return ch;
}


void LCD_GLASS_WriteChar(uint8_t* ch, uint8_t point, uint8_t column, uint8_t position) {
    
    uint8_t i, z, seg, x, b, t;
    uint8_t seg_map[4] = {0, 1, 22, 23};
    uint16_t c;

    c = LCD_Conv_Char_Seg(ch, point, column);

    // Loop for COMMON (0-4)
    for(z=0; z<4; z++) {
        //d = (uint8_t)( (c>>(12-(4*z))) & 0xFF);

        // Loop form SEGMENTS MAP (0-4) (var. seg_map)
        for(i=0; i<4; i++) {

            // calculate segment for digit num (position)
            seg = 2 * position;
            if (i < 2) {
                seg = seg_map[i] + seg;
            } else {
                seg = seg_map[i] - seg;
            }

            // calculate pixel position for segment and columns in RAM array
            t = (28 * z) + seg;
            x = (uint8_t) ( t / 8);
            b = (uint8_t) (t % 8);

            // check mask bit if is set or clear
            if ( ( ((uint8_t)( (c>>(12-(4*z))) & 0xFF)) >> i) & 0x01 ) {
                // set pixel
                LCD->RAM[x] |= (1<<b);
            } else {
                // clear pixel
                LCD->RAM[x] &= ~(1<<b);
            }
        }
    }
}