#include "sleep_handling.h"

/* Configure button for sleep mode. */
void sleep_init (void) 
{
    sleep_button = button_init (&button1_cfg);
    button_poll_count_set (BUTTON_POLL_COUNT (BUTTON_POLL_RATE));

    /* Set mcu wakeup registers. */
    // mcu_sleep_wakeup_set(&mcu_sleep_wakeup_cfg); 
}

/* Sleep event handling. */
void enter_sleep_mode (void)
{
    disable_led_strip();
    pio_output_low(RADIO_ENABLE_PIO);
    pio_output_low(H_SLEEP_PIO);
    pio_output_high(LED_ERROR_PIO);
    pio_output_high(LED_STATUS_PIO);
    // mcu_sleep(&mcu_sleep_cfg);
}

/* Wake-up event handling. */
void exit_sleep_mode (void)
{
    pio_output_high(RADIO_ENABLE_PIO);
    pio_output_high(H_SLEEP_PIO);
}

/* Poll button for sleep mode. */
void sleep_mode_task (void) 
{
    button_poll (sleep_button);

    if (button_released_p (sleep_button)) { /* Button is released. */
        enter_sleep_mode ();  

        /* Wait until button is pressed agian. */  
        do {
            button_poll (sleep_button);
        } while (!button_released_p (sleep_button));
        
        exit_sleep_mode ();
    }
}