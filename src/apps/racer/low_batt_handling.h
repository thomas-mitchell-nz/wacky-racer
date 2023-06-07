#ifndef LOW_BATT_HANDLING_H
#define LOW_BATT_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "target.h"
#include "pacer.h"
#include "adc.h"
#include "pio.h"
#include "mcu.h"
#include "sleep_handling.h"

/* Macros. */
#define NUM_LEDS        15
#define LOW_BATT_VAL    2500

/* ADC configuration. */
static const adc_cfg_t adc_cfg =
{
    .bits = 12,
    .channels = BIT (ADC_CHANNEL_1),
    .trigger = ADC_TRIGGER_SW,
    .clock_speed_kHz = 1000
};

/* Variables. */
uint16_t adc_data[1];
adc_t adc;

/* Configure ADC for low battery detection. */
void low_battery_init (void);

/* Low battery task handling. */
void low_batt_task (void);

#endif /* LOW_BATT_HANDLING_H */