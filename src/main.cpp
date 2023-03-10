#include "lamp.h"
#include "delay.h"

#define MAX_EFFECTS 5

microLED<NUMLEDS, LED_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_AVER> strip;
EncButton<EB_TICK, 2> btn;

static bool lampEnabled = false;
static int effect = 0;

mGradient<4> flameGradient = {
    .colors = {mBlack, mRed, mYellow, mWhite}};

uint32_t flameNoiseOffset = 0;

void resetEffects()
{
    flameNoiseOffset = 0;
}

void handleControls()
{
    btn.tick();

    if (btn.click())
    {
        if (!lampEnabled)
        {
            return;
        }

        effect++;

        resetEffects();

        if (effect > MAX_EFFECTS)
        {
            effect = 0;
        }

        Serial.print("EFFECT:");
        Serial.println(effect);
    }

    if (btn.isHolded())
    {
        lampEnabled = !lampEnabled;

        if (!lampEnabled)
        {
            strip.clear();
            strip.show();

            Serial.println("Lamp disabled");
            return;
        }

        Serial.println("Lamp enabled");
    }
}

void rainbow()
{
    static byte counter = 0;
    for (int i = 0; i < NUMLEDS; i++)
    {
        strip.set(i, mWheel8(counter + i * 128 / NUMLEDS));
    }
    counter += 3;
}

void flame()
{
    for (int i = 0; i < NUMLEDS; i++)
    {
        // проходим по всей ленте
        // inoise8 вернёт 0-255
        // градиент будет брать значение шума, размер градиента 255 (как максимум шума)
        // i*50 - шаг шума по горизонтали
        // count - общее движение шума по вертикали
        strip.leds[i] = flameGradient.get(inoise8(i * 50, flameNoiseOffset), 255);
    }
    flameNoiseOffset += 10;
}

void effectHandler()
{
    switch (effect)
    {
    case 0:
    {
        strip.fill(mWhite);
        break;
    }
    case 1:
    {
        strip.fill(mPurple);
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
        rainbow();
        break;
    }
    case 5:
    {
        flame();
        break;
    }
    }
}

void setup()
{
    Serial.begin(115200);
    strip.setBrightness(255);
}

void loop()
{
    handleControls();

    if (lampEnabled)
    {
        if (__delay(30))
        {
            effectHandler();

            // display
            strip.show();
        }
    }
}