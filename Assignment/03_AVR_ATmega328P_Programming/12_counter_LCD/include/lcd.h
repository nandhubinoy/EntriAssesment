#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

// LCD Pin Definitions (Adjust these according to your wiring)
#define LCD_PORT PORTD
#define LCD_DDR  DDRD
#define RS_PIN   PD2
#define EN_PIN   PD3
#define D4_PIN   PD4
#define D5_PIN   PD5
#define D6_PIN   PD6
#define D7_PIN   PD7

class LCD {
public:
    LCD();
    void init();
    void clear();
    void setCursor(uint8_t col, uint8_t row);
    void print(const char* str);
    void print(uint32_t num, uint8_t digits = 9); // Specifically for 9-digit numbers

private:
    void sendCommand(uint8_t cmd);
    void sendData(uint8_t data);
    void sendNibble(uint8_t nibble);
    void pulseEnable();
};

#endif /* LCD_H_ */