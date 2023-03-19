#ifndef LAMP_EFFECTS_H_
#define LAMP_EFFECTS_H_

#include "Arduino.h"
#include "Lamp.h"

mGradient<4> flameGradient = {
    .colors = {mBlack, mRed, mYellow, mWhite}};

uint32_t flameNoiseOffset = 0;

void switchEffect()
{
    uint32_t color = mRed;
    if (lampEnabled) {
        color = mPurple;
    }

    strip.clear();
    strip.show();

    byte row = 7;
    for (int i = 0; i < NUMLEDS - 1; i += row)
    {
        strip.clear();
        strip.fill(i, i + row, color);
        strip.show();
        
        if (i == 0) {
            delay(300);
        }
        delay(30);
    }

    for (int i = NUMLEDS - 1; i > 0; i -= row)
    {
        strip.clear();
        strip.fill(i - row, i, color);
        strip.show();
        delay(30);
    }
}

void rainbow()
{
    static byte counter = 0;
    for (int i = 0; i < NUMLEDS; i++)
    {
        strip.set(i, mWheel8(counter + i * 255 / NUMLEDS));
    }
    counter += 3;
}

void flame()
{
    for (int i = 0; i < NUMLEDS; i++)
    {
        strip.leds[i] = flameGradient.get(inoise8(i * 50, flameNoiseOffset), 255);
    }
    flameNoiseOffset += 10;
}

void resetEffects()
{
    flameNoiseOffset = 0;
}

void handleEffects()
{
    switch (lampEffect)
    {
    case 0:
    {
        flame();
        break;
    }
    case 1:
    {
        rainbow();
        break;
    }
    case 2:
    {
        strip.fill(mMaroon);
        break;
    }
    case 3:
    {
        strip.fill(mAqua);
        break;
    }
    case 4:
    {
        strip.fill(mPurple);
        break;
    }
    case 5:
    {
        strip.fill(mWhite);
        break;
    }
    case 6:
    {
        strip.fill(mOrange);
        break;
    }
    case 7:
    {
        strip.fill(mNavy);
        break;
    }
    }
}

#endif