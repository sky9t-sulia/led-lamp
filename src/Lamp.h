#ifndef LAMP_H_
#define LAMP_H_

#define LED_PIN 5
#define NUMLEDS 85
#define COLOR_DEBTH 3
#define MAX_EFFECTS 8

#define BRIGHTNES_STEP 15

#include "Arduino.h"
#include "microLED.h"
#include <FastLEDsupport.h>
#include <EncButton.h>

static bool lampEnabled = false;
static byte lampBrightnes = 210;
static byte lampEffect = 0;
microLED<NUMLEDS, LED_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_AVER> strip;

void brightnesChange()
{
    strip.setBrightness(lampBrightnes);
}

#include "Helper.h"
#include "Effects.h"

void lampStatus(bool enabled)
{
    if (lampEnabled == enabled) return;

    if (!enabled)
    {
        lampEnabled = false;
        switchEffect();

        strip.clear();
        strip.show();
        return;
    }

    lampEnabled = true;
    switchEffect();
    strip.clear();
    strip.show();
}

#include "Controls.h"
#include "IR.h"

void lampInit()
{
    strip.setBrightness(lampBrightnes);
}

#endif