#ifndef LED_HANDLING_H
#define LED_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "target.h"
#include "ledbuffer.h"
#include "ledtape.h"
#include "pio.h"
#include "mcu.h"

/* Macros. */
#define NUM_LEDS 12

/* Variables. */
int led_strip_counter; 
ledbuffer_t *leds;

enum Colours {RED, GREEN, BLUE};

/* Configure status and error LEDs. */
void led_init (void);

/* Configure LED strip. */
void led_strip_init (void);

/* LED strip task handling. */
void led_strip_task (void); 

/* Disable LED strip. */
void disable_led_strip (void);

/* Set led strip colour to red, green, or blue. */
void set_led_strip_colour (int colour);

#endif /* LED_HANDLING_H */