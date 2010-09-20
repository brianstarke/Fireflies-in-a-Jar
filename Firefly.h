/*
  Author: Brian Starke, September 19, 2010 <brian.starke@gmail.com>
  Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef Firefly_h
#define Firefly_h

#include "WProgram.h"

class Firefly
{
    public:
        Firefly(int red_pin, int green_pin, int blue_pin);
        void set_color(unsigned char red, unsigned char green, unsigned char blue);
        void set_max_color_value(int value);
        void fade_to(unsigned char color[], int speed);
        void fade_to(unsigned char red, unsigned char green, unsigned char blue, int speed);

        void firefly_blink();
        void burst();
        void sparkle();
		void go_full_color(int r_g_or_b);

    private:
        unsigned char highest_rgb_value(unsigned char red, unsigned char green, unsigned char blue);
        unsigned char highest_rgb_value();

        int _pin[3];
        int _rgb_color[3];
        int _max_color_value;
};
#endif
