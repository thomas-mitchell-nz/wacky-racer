/* File:   ledtape_test2.c
   Author: B Mitchell, UCECE
   Date:   14 April 2021
   Descr:  Test ledtape
*/

#include <pio.h>
#include "mcu.h"
#include "target.h"
#include "pacer.h"
#include "ledbuffer.h"

#define NUM_LEDS 23

/*
    This is an alternative method for driving the LED tape using the ledbuffer
    module that is included in the ledtape driver.

    The buffer acts like a small framebuffer upon which you can set RGB values
    at specific positions (not GRB, it handles the translation automatically).
    It also makes it easy to make patterns, shuffle them allow the strip, and
    clear it later. See ledbuffer.h for more details (CTRL-Click it in VS Code).
*/

int
main (void)
{
    int count = 0;

    ledbuffer_t *leds = ledbuffer_init (LEDTAPE_PIO, NUM_LEDS);

    

    pacer_init(30);

    while (1)
    {
        pacer_wait();

        if (count++ == NUM_LEDS)
        {
            // wait for a revolution
            ledbuffer_clear(leds);
            ledbuffer_set(leds, 0, 200, 255, 0);
            ledbuffer_set(leds, NUM_LEDS / 2, 200, 255, 0);
            count = 0;
        }

        ledbuffer_write (leds);
        ledbuffer_advance (leds, 1);
    }
}
