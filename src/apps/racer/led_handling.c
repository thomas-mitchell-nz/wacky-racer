#include "led_handling.h"

/* Configure status and error LEDs. */
void led_init (void) 
{
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
}

/* Configure LED strip. */
void led_strip_init (void) 
{
    led_strip_counter = 0;
    leds = ledbuffer_init (LEDTAPE_PIO, NUM_LEDS);
}

/* LED strip task handling. */
void led_strip_task (void) 
{
    if (led_strip_counter++ == NUM_LEDS) { /* Wait for a revolution. */
        ledbuffer_clear(leds);
        ledbuffer_set(leds, 0, 255, 69, 0);
        ledbuffer_set(leds, NUM_LEDS / 2, 255, 69, 0);
        led_strip_counter = 0;
    }

    ledbuffer_write (leds);
    ledbuffer_advance (leds, 1);
}

/* Disable LED strip. */
void disable_led_strip (void) 
{
    ledbuffer_clear (leds);
    ledbuffer_write (leds);
}

/* Set led strip colour to red, green, or blue. */
void set_led_strip_colour (int colour) 
{
    int red = 0;
    int blue = 0;
    int green = 0;

    /* Get colour. */
    switch (colour) {
        case (RED):
            red = 255;
            break;
        case (GREEN):
            green = 255;
            break;
        case (BLUE):
            blue = 255;
            break;
    }

    /* Set all LEDs to desired colour. */
    ledbuffer_clear(leds);
    for (int jj = 0; jj < NUM_LEDS; jj++) {
        ledbuffer_set(leds, jj, red, green, blue);      
    }
    ledbuffer_write (leds); 
}