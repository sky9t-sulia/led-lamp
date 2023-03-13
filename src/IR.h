#ifndef LAMP_IR_H_
#define LAMP_IR_H_

#include "Arduino.h"
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 6

/* --------------- CONTROLLER COMMANDS ------------------ */
#define NUM_PAD_1 0x44
#define NUM_PAD_2 0x43
#define NUM_PAD_3 0x7
#define NUM_PAD_4 0x9
#define NUM_PAD_5 0x16
#define NUM_PAD_6 0xD
#define NUM_PAD_7 0xC
#define NUM_PAD_8 0x5E

#define BRIGHTNES_LOW 0x8
#define BRIGHTNES_HIGH 0x5A

#define LAMP_ON 0x45
#define LAMP_OFF 0x47
#define LAMP_TIMER 0x46
/* ------------------------------------------------------ */

void IRInit()
{
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void handleIRController(uint16_t command)
{
    if (command == LAMP_ON) {
        lampStatus(true);
        return;
    }
    if (command == LAMP_OFF) {
        lampStatus(false);
        return;
    }

    if (command == BRIGHTNES_HIGH) {
        if (lampBrightnes < 255) {
            lampBrightnes += BRIGHTNES_STEP;
        }
        brightnesChange();
        return;
    }

    if (command == BRIGHTNES_LOW) {
        if (lampBrightnes > 0) {
            lampBrightnes -= BRIGHTNES_STEP;
            brightnesChange();
        }
        return;
    }

    switch (command)
    {
    case NUM_PAD_1:
    {
        lampEffect = 0;
        break;
    }
    case NUM_PAD_2:
    {
        lampEffect = 1;
        break;
    }
    case NUM_PAD_3:
    {
        lampEffect = 2;
        break;
    }
    case NUM_PAD_4:
    {
        lampEffect = 3;
        break;
    }
    case NUM_PAD_5:
    {
        lampEffect = 4;
        break;
    }
    case NUM_PAD_6:
    {
        lampEffect = 5;
        break;
    }
    case NUM_PAD_7:
    {
        lampEffect = 6;
        break;
    }
    case NUM_PAD_8:
    {
        lampEffect = 7;
        break;
    }
    }
}

void handleIR()
{
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.protocol == NEC)
        {
            handleIRController(IrReceiver.decodedIRData.command);
        }

        IrReceiver.resume();
    }
}

#endif