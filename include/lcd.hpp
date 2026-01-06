#ifndef LCD_HPP
#define LCD_HPP

#include <LiquidCrystal_I2C.h>

class LCD {
    private:
        LiquidCrystal_I2C lcd;
        uint8_t lcd_cols;
        uint8_t lcd_rows;
    public:
        LCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
        ~LCD();
        void LCD_SetCursor(uint8_t col, uint8_t row);
        void LCD_Print(const String &s);
        void LCD_PrintLCD(const String &first = "", const String &second = "", const String &third = "", const String &fourth = "");
        void LCD_ClrScr();
};

#endif
