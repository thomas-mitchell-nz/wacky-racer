#ifndef PWM_HANDLING_H
#define PWM_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pwm.h"
#include "pio.h"
#include "stdio.h"
#include "panic.h"
#include "target.h"
#include "usb_serial.h"

/* Define macros. */
#define PWM_FREQ_HZ 100e3
#define FAST_SPEED 1000
#define SLOW_SPEED 920
#define TURN_SPEED 800

/* Define typedefs. */
typedef struct
{
    uint8_t ma1_duty;
    uint8_t ma2_duty;
    uint8_t mb1_duty;
    uint8_t mb2_duty;
} motor_duty_cycles_t;

/* Motor objects. */
pwm_t ma1;
pwm_t ma2;
pwm_t mb1;
pwm_t mb2; 

/* Initialise H-bridge and configure motors. */
void h_bridge_init (void); 

/* Set motor duty cycles. */
void set_motor_duty_cycles (int ma1_duty, int ma2_duty, int mb1_duty, int mb2_duty);

/* Set motor duty from USB serial. */
void set_duty_from_serial (void); 

/* Set car direction. */
void set_direction (int8_t command);

#endif /* PWM_HANDLING_H */