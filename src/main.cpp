#include "Lamp.h"

void setup()
{
    lampInit();
    IRInit();
}

void loop()
{
    handleControls();
    handleIR();

    if (lampEnabled)
    {
        if (lamp_delay(30))
        {
            handleEffects();

            // display
            strip.show();
        }
    }
}