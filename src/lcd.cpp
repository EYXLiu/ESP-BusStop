#include <lcd.hpp>

LCD::LCD(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows) : lcd(lcd_Addr, lcd_cols, lcd_rows), lcd_cols(lcd_cols), lcd_rows(lcd_rows) {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
} 

LCD::~LCD() {}

void LCD::LCD_SetCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

void LCD::LCD_Print(const String &s) {
    char buffer[21];
    int i = 0;
    for (; i < lcd_cols && s[i] != '\0'; i++) {
        buffer[i] = s[i];
    }
    for (; i < lcd_cols; i++) {
        buffer[i] = ' ';
    }
    buffer[lcd_cols] = '\0';
    lcd.print(buffer);
}

void LCD::LCD_PrintLCD(const String &first, const String &second, const String &third, const String &fourth) {
    LCD_SetCursor(0,0);
    LCD_Print(first);
    LCD_SetCursor(0,1);
    LCD_Print(second);
    if (lcd_rows > 2) {
        LCD_SetCursor(0,2);
        LCD_Print(third);
        LCD_SetCursor(0,3);
        LCD_Print(fourth);
    }
}

void LCD::LCD_ClrScr() {
    lcd.clear();
}
