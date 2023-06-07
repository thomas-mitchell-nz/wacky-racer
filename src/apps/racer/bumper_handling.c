#include "bumper_handling.h"

/* Configure bumber sensor. */
void bumper_init (void) 
{ 
    pio_config_set (BUMPER_PIO, PIO_PULLUP);
}

/* Bumper task handling. */
void bumper_task (void) 
{
    /* Limit switch hit. */
    if (!pio_input_get(BUMPER_PIO)) {   
        int bumper_counter = 0;
        set_direction(STATIONARY);
        set_led_strip_colour(RED);

        /* Send command for 0.5 sec. */
        while (bumper_counter < (PACER_RATE/2)) {  
            pacer_wait();
            send_command(DEAD_COMMAND);
            bumper_counter++;
        }

        /* Pause for 5 sec, then escape collision. */
        delay_ms(7000); /* 7000 = 5s */                
        set_direction(FORWARD_SLOW_STRAIGHT);
        delay_ms(200);
        set_direction(STATIONARY);
    }
}