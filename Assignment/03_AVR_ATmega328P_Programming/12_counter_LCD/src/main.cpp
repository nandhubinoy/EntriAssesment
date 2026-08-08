#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

// Button Pin Definition (Connect button between Pin 8 (PB0) and GND)
#define BUTTON_PORT PORTB
#define BUTTON_PIN  PINB
#define BUTTON_DDR  DDRB
#define BUTTON_BIT  PB0

// Timing Constants
const uint16_t LONG_PRESS_TIME_MS = 2000;
const uint8_t DEBOUNCE_TIME_MS = 50;

enum class ButtonState {
    IDLE,
    PRESSED,
    LONG_PRESSED,
    WAIT_RELEASE
};

class Button {
public:
    Button() : state(ButtonState::IDLE), pressTime(0) {}

    void init() {
        // Configure as input
        BUTTON_DDR &= ~(1 << BUTTON_BIT);
        // Enable internal pull-up resistor
        BUTTON_PORT |= (1 << BUTTON_BIT);
    }

    // Call this frequently in the main loop to check button status
    // Returns 1 for short press, 2 for long press, 0 otherwise
    uint8_t check() {
        bool isPressed = !(BUTTON_PIN & (1 << BUTTON_BIT)); // Active low because of pull-up

        switch (state) {
            case ButtonState::IDLE:
                if (isPressed) {
                    _delay_ms(DEBOUNCE_TIME_MS); // Debounce
                    if (!(BUTTON_PIN & (1 << BUTTON_BIT))) {
                        state = ButtonState::PRESSED;
                        pressTime = 0;
                    }
                }
                break;

            case ButtonState::PRESSED:
                if (isPressed) {
                    pressTime += 10; // Assuming check() is called every 10ms approx
                    _delay_ms(10);
                    if (pressTime >= LONG_PRESS_TIME_MS) {
                        state = ButtonState::LONG_PRESSED;
                        return 2; // Long press detected
                    }
                } else {
                    state = ButtonState::IDLE;
                    if (pressTime > 0) { // Short press confirmed upon release
                        return 1;
                    }
                }
                break;

            case ButtonState::LONG_PRESSED:
            case ButtonState::WAIT_RELEASE:
                if (!isPressed) {
                    _delay_ms(DEBOUNCE_TIME_MS);
                    state = ButtonState::IDLE;
                }
                break;
        }
        return 0; // No action needed yet
    }

private:
    ButtonState state;
    uint16_t pressTime;
};

int main(void) {
    // Initialize objects
    LCD lcd;
    Button btn;

    lcd.init();
    btn.init();

    uint32_t counter = 0;

    // Initial Display
    lcd.setCursor(0, 0);
    lcd.print("Counter:");
    lcd.setCursor(0, 1);
    lcd.print(counter, 9); // Display 000000000

    while (1) {
        uint8_t btnAction = btn.check();

        if (btnAction == 1) {
            // Short Press: Increment
            if (counter < 999999999) {
                counter++;
            }
            lcd.setCursor(0, 1);
            lcd.print(counter, 9);
        } else if (btnAction == 2) {
            // Long Press: Reset
            counter = 0;
            lcd.setCursor(0, 1);
            lcd.print(counter, 9);
        }
    }

    return 0;
}