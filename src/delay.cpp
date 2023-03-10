#include "delay.h"

static uint32_t timer = 0;

bool __delay(uint32_t ms) {
    if (millis() - timer >= ms) {
        timer = millis();

        return true;
    }
    return false;
}