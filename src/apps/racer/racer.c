/* File:   racer.c
   Author: T. J. MITCHELL
   Date:   9 April 2023
   Descr:  Racer program
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "target.h"
#include "delay.h"
#include "panic.h"
#include "pacer.h"
#include "pwm.h"
#include "pio.h"
#include "mcu.h"
#include "usb_serial.h"
#include "led_handling.h"
#include "pwm_handling.h"
#include "nrf_handling.h"
#include "sleep_handling.h"
#include "bumper_handling.h"
#include "low_batt_handling.h"

int main (void)
{
    /* Pacer counters. */
    int led_tick=0;
    int serial_tick=0;
    int radio_tick=0;
    int bumper_tick=0;
    int sleep_tick=0;
    int low_batt_tick=0;
    int led_strip_tick=0;

    /* Initialise modules. */
    pacer_init (PACER_RATE);
    usb_serial_stdio_init ();
    led_init();
    led_strip_init();
    low_battery_init();
    h_bridge_init ();
    nrf_init ();    
    sleep_init ();  
    bumper_init();  

    /* Infinite loop. */
    while (1)
    {
        /* Wait until next clock tick. */
        pacer_wait ();

        /* Increment counters. */
        serial_tick++;
        led_tick++;
        radio_tick++;
        bumper_tick++;
        sleep_tick++;
        low_batt_tick++;
        led_strip_tick++;

        /* Schedular. */
        if (led_tick >= (PACER_RATE/LED_TASK_RATE)) {
            pio_output_toggle (LED_STATUS_PIO);
            led_tick = 0;
        }
        
        if (serial_tick >= (PACER_RATE/SERIAL_TASK_RATE)) {
            set_duty_from_serial ();
            serial_tick = 0;
        }
        
        if (radio_tick >= (PACER_RATE/RADIO_TASK_RATE)) {
            int8_t command = read_command ();
            if (command > 0) set_direction (command);
            radio_tick = 0;
        }  
        
        if (bumper_tick >= (PACER_RATE/BUMPER_TASK_RATE)) {
            bumper_task();
            bumper_tick = 0;
        }

        if (sleep_tick >= (PACER_RATE/BUTTON_POLL_RATE)) {
            sleep_mode_task();
            sleep_tick = 0;
        }

        if (led_strip_tick >= (PACER_RATE/LEDSTRIP_POLL_RATE)) {
            led_strip_task();
            led_strip_tick = 0;
        }
        
        if (low_batt_tick >= (PACER_RATE/ADC_POLL_RATE)) {
            low_batt_task();
            low_batt_tick = 0;
        }
    }

    return 0;
}