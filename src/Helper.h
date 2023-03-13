#ifndef LAMP_HELPER_H_
#define LAMP_HELPER_H_

#include "Arduino.h"

static uint32_t timer = 0;

bool lamp_delay(uint32_t ms) {
    if (millis() - timer >= ms) {
        timer = millis();

        return true;
    }
    return false;
}

#endif