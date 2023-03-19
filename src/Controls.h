#ifndef LAMP_CONTROLS_H_
#define LAMP_CONTROLS_H_

#include "Arduino.h"
#include "Lamp.h"

EncButton<EB_TICK, 2> btn;

void handleControls()
{
    btn.tick();

    if (btn.click())
    {
        if (!lampEnabled)
        {
            return;
        }

        lampEffect++;

        resetEffects();

        if (lampEffect > MAX_EFFECTS)
        {
            lampEffect = 0;
        }
    }

    if (btn.isHolded())
    {
        if (lampEnabled)
        {
            lampStatus(false);
        } else {
            lampStatus(true);
        }
    }
}

#endif