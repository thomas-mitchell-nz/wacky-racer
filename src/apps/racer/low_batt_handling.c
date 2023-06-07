#include "low_batt_handling.h"

/* Configure ADC for low battery detection. */
void low_battery_init (void)
{
    adc = adc_init (&adc_cfg);
}

/* Low battery task handling. */
void low_batt_task (void) 
{
    adc_read (adc, adc_data, sizeof(adc_data)); 

    if (adc_data[0] <= LOW_BATT_VAL) {  /* Battery low. */
        int led_counter = 0;
        enter_sleep_mode(); 

        /* Poll ADC until battery increases from low. */
        while (adc_data[0] <= LOW_BATT_VAL) {
            adc_read (adc, adc_data, sizeof(adc_data));
            led_counter++;
            pacer_wait();
            
            /* Flash error LED. */
            if (led_counter >= (PACER_RATE/LED_TASK_RATE)) {
                pio_output_toggle(LED_ERROR_PIO);
                led_counter = 0;
            }
        }
        
        /* Turn off error LED. */
        pio_output_high(LED_ERROR_PIO);
        exit_sleep_mode();
    }
}