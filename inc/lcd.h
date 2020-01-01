#ifndef STM8L_LCD__H
#define STM8L_LCD__H

/*  =========================================================================
                                 LCD MAPPING
    =========================================================================
            A
        ----------
        |\   |J  /|   |_| COL
       F| H  |  K |B
        |  \ | /  |    _
        --G-- --M--   |_| COL
        |   /| \  |
       E|  Q |  N |C
        | /  |P  \|    _
        -----------   |_| DP
            D
 An LCD character coding is based on the following matrix:

       C0  C1  C2  C3
      { E , D , P , N  }
      { M , C , COL,DP }
      { B , A , K , J  }
      { G , F , Q , H  }
 
 The character 'A' for example is:
  -------------------------------
 LSB	{ 1 , 0 , 0 , 0 }
	    { 1 , 1 , 0 , 0 }
        { 1 , 1 , 0 , 0 }
 MSB 	{ 1 , 1 , 0 , 0 }
  -------------------
  'A' =  F    E   0   0 hexa
*/



void lcd_setup(void);
void LCD_ContrastConfig(uint8_t LCD_Contrast);
void LCD_GLASS_Clear(void);
uint16_t LCD_Conv_Char_Seg(uint8_t* c, uint8_t point, uint8_t column);
void LCD_GLASS_WriteChar(uint8_t* ch, uint8_t point, uint8_t column, uint8_t position);

#endif