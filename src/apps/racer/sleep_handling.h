#ifndef SLEEP_HANDLING_H
#define SLEEP_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "target.h"
#include "button.h"
#include "mcu_sleep.h"
#include "led_handling.h"
#include "mcu.h"
#include "pio.h"
#include "spi.h"

/* Wakeup configuration. */
static const mcu_sleep_wakeup_cfg_t mcu_sleep_wakeup_cfg =
{
    .pio = SLEEP_BUTTON_PIO,
    .active_high = false
};

/* Sleep mode. */
static const mcu_sleep_mode_t mcu_sleep_mode = MCU_SLEEP_MODE_WAIT;

/* Sleep configuration. */
static const mcu_sleep_cfg_t mcu_sleep_cfg = {
    .mode = mcu_sleep_mode
};

/* Button configuration.  */
static const button_cfg_t button1_cfg =
{
    .pio = SLEEP_BUTTON_PIO
};

/* Button object. */
button_t sleep_button;

/* Initialise sleep mode. */
void sleep_init (void);

/* Sleep event handling. */
void enter_sleep_mode (void);

/* Wake-up event handling. */
void exit_sleep_mode (void);

/* Poll button for sleep mode. */
void sleep_mode_task (void);

#endif /* SLEEP_HANDLING_H */