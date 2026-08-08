#include "lcd.h"
#include <stdio.h> // For sprintf

LCD::LCD() {}

void LCD::pulseEnable() {
    LCD_PORT |= (1 << EN_PIN);
    _delay_us(1);
    LCD_PORT &= ~(1 << EN_PIN);
    _delay_us(100);
}

void LCD::sendNibble(uint8_t nibble) {
    // Clear data pins
    LCD_PORT &= ~((1 << D4_PIN) | (1 << D5_PIN) | (1 << D6_PIN) | (1 << D7_PIN));
    
    // Set data pins based on nibble
    if (nibble & 0x01) LCD_PORT |= (1 << D4_PIN);
    if (nibble & 0x02) LCD_PORT |= (1 << D5_PIN);
    if (nibble & 0x04) LCD_PORT |= (1 << D6_PIN);
    if (nibble & 0x08) LCD_PORT |= (1 << D7_PIN);
    
    pulseEnable();
}

void LCD::sendCommand(uint8_t cmd) {
    LCD_PORT &= ~(1 << RS_PIN); // RS = 0 for command
    sendNibble(cmd >> 4);       // Send upper nibble
    sendNibble(cmd & 0x0F);     // Send lower nibble
    if (cmd < 4) _delay_ms(2);  // Commands 1 and 2 take longer
    else _delay_us(40);
}

void LCD::sendData(uint8_t data) {
    LCD_PORT |= (1 << RS_PIN);  // RS = 1 for data
    sendNibble(data >> 4);      // Send upper nibble
    sendNibble(data & 0x0F);    // Send lower nibble
    _delay_us(40);
}

void LCD::init() {
    // Set LCD pins as output
    LCD_DDR |= (1 << RS_PIN) | (1 << EN_PIN) | (1 << D4_PIN) | (1 << D5_PIN) | (1 << D6_PIN) | (1 << D7_PIN);
    
    _delay_ms(50); // Wait for power to stabilize

    // 4-bit mode initialization sequence
    LCD_PORT &= ~(1 << RS_PIN); // RS = 0
    
    sendNibble(0x03); _delay_ms(5);
    sendNibble(0x03); _delay_us(150);
    sendNibble(0x03);
    sendNibble(0x02); // Set to 4-bit mode

    sendCommand(0x28); // 4-bit mode, 2 lines, 5x8 font
    sendCommand(0x0C); // Display ON, Cursor OFF, Blink OFF
    sendCommand(0x06); // Increment cursor
    clear();
}

void LCD::clear() {
    sendCommand(0x01);
    _delay_ms(2);
}

void LCD::setCursor(uint8_t col, uint8_t row) {
    uint8_t address = col;
    if (row == 1) address += 0x40;
    sendCommand(0x80 | address);
}

void LCD::print(const char* str) {
    while (*str) {
        sendData(*str++);
    }
}

void LCD::print(uint32_t num, uint8_t digits) {
    char buffer[16];
    
    // Safety check to prevent buffer overflow
    if (digits > 15) digits = 15;
    
    // Null-terminate the string
    buffer[digits] = '\0';
    
    // Extract digits right-to-left and automatically add leading zeros
    for (int i = digits - 1; i >= 0; i--) {
        buffer[i] = (num % 10) + '0'; // Convert integer to ASCII character
        num /= 10;
    }
    
    print(buffer);
}

#if 0
#include "lcd.h"
#include <stdio.h> // For sprintf

LCD::LCD() {}

void LCD::pulseEnable() {
    LCD_PORT |= (1 << EN_PIN);
    _delay_us(1);
    LCD_PORT &= ~(1 << EN_PIN);
    _delay_us(100);
}

void LCD::sendNibble(uint8_t nibble) {
    // Clear data pins
    LCD_PORT &= ~((1 << D4_PIN) | (1 << D5_PIN) | (1 << D6_PIN) | (1 << D7_PIN));
    
    // Set data pins based on nibble
    if (nibble & 0x01) LCD_PORT |= (1 << D4_PIN);
    if (nibble & 0x02) LCD_PORT |= (1 << D5_PIN);
    if (nibble & 0x04) LCD_PORT |= (1 << D6_PIN);
    if (nibble & 0x08) LCD_PORT |= (1 << D7_PIN);
    
    pulseEnable();
}

void LCD::sendCommand(uint8_t cmd) {
    LCD_PORT &= ~(1 << RS_PIN); // RS = 0 for command
    sendNibble(cmd >> 4);       // Send upper nibble
    sendNibble(cmd & 0x0F);     // Send lower nibble
    if (cmd < 4) _delay_ms(2);  // Commands 1 and 2 take longer
    else _delay_us(40);
}

void LCD::sendData(uint8_t data) {
    LCD_PORT |= (1 << RS_PIN);  // RS = 1 for data
    sendNibble(data >> 4);      // Send upper nibble
    sendNibble(data & 0x0F);    // Send lower nibble
    _delay_us(40);
}

void LCD::init() {
    // Set LCD pins as output
    LCD_DDR |= (1 << RS_PIN) | (1 << EN_PIN) | (1 << D4_PIN) | (1 << D5_PIN) | (1 << D6_PIN) | (1 << D7_PIN);
    
    _delay_ms(50); // Wait for power to stabilize

    // 4-bit mode initialization sequence
    LCD_PORT &= ~(1 << RS_PIN); // RS = 0
    
    sendNibble(0x03); _delay_ms(5);
    sendNibble(0x03); _delay_us(150);
    sendNibble(0x03);
    sendNibble(0x02); // Set to 4-bit mode

    sendCommand(0x28); // 4-bit mode, 2 lines, 5x8 font
    sendCommand(0x0C); // Display ON, Cursor OFF, Blink OFF
    sendCommand(0x06); // Increment cursor
    clear();
}

void LCD::clear() {
    sendCommand(0x01);
    _delay_ms(2);
}

void LCD::setCursor(uint8_t col, uint8_t row) {
    uint8_t address = col;
    if (row == 1) address += 0x40;
    sendCommand(0x80 | address);
}

void LCD::print(const char* str) {
    while (*str) {
        sendData(*str++);
    }
}

void LCD::print(uint32_t num, uint8_t digits) {
    char buffer[16];
    // Format the number with leading zeros (e.g., "%09lu" for 9 digits)
    sprintf(buffer, "%0*lu", digits, num);
    print(buffer);
}
#endif