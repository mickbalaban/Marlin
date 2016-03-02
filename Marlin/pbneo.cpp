#include "Adafruit_NeoPixel.h"
#include <avr/power.h>
#include "pbneo.h"
#include "Configuration.h"
#include "Marlin.h"

#define FRAME_SPEED 50

Adafruit_NeoPixel neo = Adafruit_NeoPixel(1, PBNEO_PIN, NEO_GRB + NEO_KHZ800);

int current_animation;
int current_frame;
long next_frame_event;
int current_color;

int darken(int rgb)
{
   return rgb;
}

void sleep_animation()
{
    if (current_frame < 51) {
        neo.setPixelColor(0, neo.Color(current_frame,current_frame,current_frame));

    }
    else if (current_frame > 50 && current_frame < 101)
    {
        neo.setPixelColor(0, neo.Color(100-current_frame, 100-current_frame, 100-current_frame));
    }
    else if (current_frame > 150) {
        current_frame = 0;
        return;
    }
    else
    {
        neo.setPixelColor(0, neo.Color(0, 0, 0));
    }
    neo.show();
}

void  heating_animation()
{
    if (current_frame <= 25) {
        neo.setPixelColor(0, neo.Color(25+current_frame,10+current_frame,0));
    }

    else {
        current_frame = 0;
        return;
    }
    neo.show();
}

void  danger_animation()
{
    if (current_frame <= 25) {
        neo.setPixelColor(0, neo.Color(25+current_frame,0,0));
    }

    else {
        current_frame = 0;
        return;
    }
    neo.show();
}

void active_animation()
{
    if (current_frame > 1) {
        neo.setPixelColor(0, neo.Color(86/2,193/2,0));
        neo.show();
    }
    current_frame = 0;
}

void ready_animation()
{
    if (current_frame > 1) {
        neo.setPixelColor(0, neo.Color(255,255,255));
        neo.show();
    }
    current_frame = 0;
}


void pbneo_set_animation(int anim)
{
    current_animation = anim;
}

int pbneo_get_animation()
{
    return current_animation;
}

void next_frame()
{
    switch (current_animation)
    {
        case HEATING_ANIMATION:
            heating_animation();
            break;
        case READY_ANIMATION:
            ready_animation();
            break;
        case ACTIVE_ANIMATION:
            active_animation();
            break;
        case DANGER_ANIMATION:
            danger_animation();
            break;
        case FILAMENTCHANGE_ANIMATION:
            danger_animation();
        case SLEEP_ANIMATION:
            sleep_animation();
        default:
            sleep_animation();
            break;
    }

}

void pbneo_update()
{
    if (next_frame_event < millis()) {
        next_frame();
        current_frame++;
        next_frame_event = millis() + FRAME_SPEED;
    }
}

void pbneo_init()
{
    neo.begin();
    current_animation = SLEEP_ANIMATION;
    current_frame = 10;
    next_frame_event = 0;
}
