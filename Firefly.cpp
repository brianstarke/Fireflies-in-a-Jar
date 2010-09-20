/*
  Author: Brian Starke, September 19, 2010 <brian.starke@gmail.com>
  Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php
*/

#include "WProgram.h"
#include "Firefly.h"

Firefly::Firefly(int red_pin, int green_pin, int blue_pin)
{
    _pin[0] = red_pin;
    _pin[1] = green_pin;
    _pin[2] = blue_pin;

    _max_color_value = 350;

    for(int x = 0; x < 3; x++) {
        pinMode(_pin[x], OUTPUT);
    }

    set_color(0,0,0);
}

void Firefly::set_color(unsigned char red, unsigned char green, unsigned char blue)
{
    _rgb_color[0] = red;
    _rgb_color[1] = green;
    _rgb_color[2] = blue;

    for(int x = 0; x < 3; x++) {
        analogWrite(_pin[x], 255-_rgb_color[x]);
    }
}

void Firefly::fade_to(unsigned char color[], int speed)
{
    fade_to(color[0], color[1], color[2], speed);
}

void Firefly::fade_to(unsigned char red, unsigned char green, unsigned char blue, int speed)
{
    int highest = highest_rgb_value(red,green,blue);

    for(int x = 0; x < highest; x++) {

        if(red > _rgb_color[0] && red != _rgb_color[0]) {
            _rgb_color[0]++;
        }

        if(red < _rgb_color[0] && red != _rgb_color[0]) {
            _rgb_color[0]--;
        }

        if(green > _rgb_color[1] && green != _rgb_color[1]) {
            _rgb_color[1]++;
        }

        if(green < _rgb_color[1] && green != _rgb_color[1]) {
            _rgb_color[1]--;
        }

        if(blue > _rgb_color[2] && blue != _rgb_color[2]) {
            _rgb_color[2]++;
        }

        if(blue < _rgb_color[2] && blue != _rgb_color[2]) {
            _rgb_color[2]--;
        }

        for(int y = 0; y < 3; y++) {
            analogWrite(_pin[y], 255-_rgb_color[y]);
        }

        delay(speed);
    }
}

/* 
blinking the firefly :

my basic concept is that fireflies fade up at different speeds, then hold that glow
for a random period of time, then fade down at a speed quicker then they faded up.

also, on occasion - they get real bright in the middle briefly.
*/
void Firefly::firefly_blink()
{
    // first select a color to light up the firefly with
    boolean color_ok = false;
    unsigned char red, green, blue;

    /* 
    i do this to keep the overall value down so they don't
    all come out white
    */
    while(!color_ok) {
        red = random(0,255);
        green = random(0,255);
        blue = random(0,255);

        if(red + green + blue < _max_color_value) {
            color_ok = true;
        }
    }

    // set the delays
    int fade_up_speed = random(4,15);
    int hold_delay = random(0,500);
    int fade_down_speed = random(1,fade_up_speed);

                                                  // light up the firefly
    fade_to(red, green, blue, fade_up_speed);

    delay(random(1,500));

    // do random event on occasion

    int event_trigger = random(1,20);

    if(event_trigger == 5) {
        burst();
    }

    if(event_trigger == 10) {
        sparkle();
    }

    if(event_trigger == 15) {
        go_full_color(random(0,3));
    }

    if(event_trigger == 12 || event_trigger == 6) {
        delay(random(300,800));
    }

    fade_to(0 , 0 ,0 , fade_down_speed);
}

void Firefly::sparkle()
{
    unsigned char original_color[3] = {_rgb_color[0], _rgb_color[1], _rgb_color[2]};

    int num_sparkles = random(4,14);

    for(int x = 0; x < num_sparkles; x++) {
        fade_to(original_color[1],original_color[2],original_color[3],1);
        fade_to(original_color[2],original_color[3],original_color[1],1);
        fade_to(original_color[3],original_color[1],original_color[2],1);
    }

    fade_to(original_color,1);
}

void Firefly::burst()
{
    unsigned char burst_color[3];
    unsigned char original_color[3] = {_rgb_color[0], _rgb_color[1], _rgb_color[2]};

    for(int x = 0; x < 3; x++) {
        if(_rgb_color[x] == highest_rgb_value()) {
            burst_color[x] = 255;
        }
        else {
            burst_color[x] = _rgb_color[x];
        }
    }

    fade_to(burst_color, 2);
    fade_to(original_color, 2);
}

void Firefly::go_full_color(int r_g_or_b)
{
    unsigned char full_color[3];
    unsigned char glow_color[3];
    unsigned char original_color[3] = {_rgb_color[0], _rgb_color[1], _rgb_color[2]};

    for(int x = 0; x < 3; x++) {
        if(x == r_g_or_b) {
            full_color[x] = 255;
            glow_color[x] = 25;
        }
        else {
            full_color[x] = 0;
            glow_color[x] = 0;
        }
    }

    int num_glows = random(5,10);

    for(int x = 0; x < num_glows; x++) {
        fade_to(full_color, 4);
        fade_to(glow_color, 4);
    }

    fade_to(original_color, 2);
}

unsigned char Firefly::highest_rgb_value(unsigned char red, unsigned char green, unsigned char blue)
{
    unsigned char highest = highest_rgb_value();

    if(red > highest) {
        highest = red;
    }

    if(green > highest) {
        highest = green;
    }

    if(blue > highest) {
        highest = blue;
    }

    return highest;
}

unsigned char Firefly::highest_rgb_value()
{
    unsigned char highest = 0;

    if(_rgb_color[0] > highest) {
        highest = _rgb_color[0];
    }

    if(_rgb_color[1] > highest) {
        highest = _rgb_color[1];
    }

    if(_rgb_color[2] > highest) {
        highest = _rgb_color[2];
    }

    return highest;
}

void Firefly::set_max_color_value(int value)
{
    _max_color_value = value;
}
