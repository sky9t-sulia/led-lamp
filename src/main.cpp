#include "Lamp.h"

void setup()
{
    Serial.begin(115200);
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