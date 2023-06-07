#ifndef BUMPER_HANDLING_H
#define BUMPER_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "target.h"
#include "pacer.h"
#include "delay.h"
#include "pio.h"
#include "mcu.h"
#include "pwm_handling.h"
#include "nrf_handling.h"
#include "led_handling.h"

/* Initialise bumper. */
void bumper_init (void);

/* Bumper task handling. */
void bumper_task (void);

#endif /* SLEEP_HANDLING_H */