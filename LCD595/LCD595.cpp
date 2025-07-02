#include "LCD595.h"

LCD595::LCD595(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)
  : _dataPin(dataPin), _clockPin(clockPin), _latchPin(latchPin) {}

void LCD595::begin() {
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);

  delay(50);
  sendNibble(0x03, false); delay(5);
  sendNibble(0x03, false); delay(5);
  sendNibble(0x03, false); delay(5);
  sendNibble(0x02, false); delay(5); // 4-bit mode

  command(0x28);
  command(0x0C);
  command(0x06);
  clear();
}

void LCD595::clear() { command(0x01); delay(2); }
void LCD595::home() { command(0x02); delay(2); }

void LCD595::setCursor(uint8_t col, uint8_t row) {
  static const uint8_t rowOffsets[] = {0x00, 0x40, 0x14, 0x54};
  command(0x80 | (col + rowOffsets[row]));
}

void LCD595::display() { command(0x0C); }
void LCD595::noDisplay() { command(0x08); }
void LCD595::cursor() { command(0x0E); }
void LCD595::noCursor() { command(0x0C); }
void LCD595::blink() { command(0x0D); }
void LCD595::noBlink() { command(0x0C); }
void LCD595::scrollDisplayLeft() { command(0x18); }
void LCD595::scrollDisplayRight() { command(0x1C); }
void LCD595::leftToRight() { command(0x06); }
void LCD595::rightToLeft() { command(0x04); }
void LCD595::autoscroll() { command(0x07); }
void LCD595::noAutoscroll() { command(0x06); }

void LCD595::print(const char *str) { while (*str) writeChar(*str++); }
void LCD595::print(char c) { writeChar(c); }
void LCD595::print(int num) { print(String(num).c_str()); }
void LCD595::print(unsigned int num) { print(String(num).c_str()); }
void LCD595::print(long num) { print(String(num).c_str()); }
void LCD595::print(unsigned long num) { print(String(num).c_str()); }

void LCD595::shiftOut595(uint8_t data) {
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, MSBFIRST, data);
  digitalWrite(_latchPin, HIGH);
}

void LCD595::pulseEnable(uint8_t data) {
  shiftOut595(data | (1 << LCD_EN));
  delayMicroseconds(1);
  shiftOut595(data & ~(1 << LCD_EN));
  delayMicroseconds(100);
}

void LCD595::sendNibble(uint8_t nibble, bool isData) {
  uint8_t data = 0;
  if (isData) data |= (1 << LCD_RS);
  if (nibble & 0x01) data |= (1 << LCD_D4);
  if (nibble & 0x02) data |= (1 << LCD_D5);
  if (nibble & 0x04) data |= (1 << LCD_D6);
  if (nibble & 0x08) data |= (1 << LCD_D7);
  pulseEnable(data);
}

void LCD595::sendByte(uint8_t value, bool isData) {
  sendNibble(value >> 4, isData);
  sendNibble(value & 0x0F, isData);
  delayMicroseconds(50);
}

void LCD595::command(uint8_t value) {
  sendByte(value, false);
}

void LCD595::writeChar(uint8_t value) {
  sendByte(value, true);
}
