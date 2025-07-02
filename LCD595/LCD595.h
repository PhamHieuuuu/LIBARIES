//Written by Phamhieuu
#ifndef LCD595_H
#define LCD595_H

#include <Arduino.h>

class LCD595 {
  public:
    LCD595(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
    void begin();
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row);
    void print(const char *str);
    void print(char c);
    void print(int num);
    void print(unsigned int num);
    void print(long num);
    void print(unsigned long num);
    void display();
    void noDisplay();
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();

  private:
    uint8_t _dataPin, _clockPin, _latchPin;
    void shiftOut595(uint8_t data);
    void pulseEnable(uint8_t data);
    void sendNibble(uint8_t nibble, bool isData);
    void sendByte(uint8_t value, bool isData);
    void command(uint8_t value);
    void writeChar(uint8_t value);

    static const uint8_t LCD_RS = 0;
    static const uint8_t LCD_EN = 1;
    static const uint8_t LCD_D4 = 2;
    static const uint8_t LCD_D5 = 3;
    static const uint8_t LCD_D6 = 4;
    static const uint8_t LCD_D7 = 5;
};

#endif
