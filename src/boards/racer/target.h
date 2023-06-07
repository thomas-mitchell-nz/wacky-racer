/* File:   racer.c
   Author: T. J. MITCHELL
   Date:   29 May 2023
   Descr:  Targets
*/

#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* Commands */
#define DEAD_COMMAND 13

enum Commands {FORWARD_SLOW_STRAIGHT=0, FORWARD_SLOW_LEFT=1, FORWARD_SLOW_RIGHT=2, 
               FORWARD_FAST_STRAIGHT=3, FORWARD_FAST_LEFT=4, FORWARD_FAST_RIGHT=5,
               BACKWARD_SLOW_STRAIGHT=6, BACKWARD_SLOW_LEFT=7, BACKWARD_SLOW_RIGHT=8,
               BACKWARD_FAST_STRAIGHT=9, BACKWARD_FAST_LEFT=10, BACKWARD_FAST_RIGHT=11,
               STATIONARY=12};

/* Task Rates */
#define PACER_RATE          100
#define BUMPER_TASK_RATE    50
#define BUTTON_POLL_RATE    50
#define RADIO_TASK_RATE     50
#define LEDSTRIP_POLL_RATE  10
#define SERIAL_TASK_RATE    2
#define LED_TASK_RATE       2
#define ADC_POLL_RATE       2

/* System clocks */
#define F_XTAL 12.00e6
#define MCU_PLL_MUL 16
#define MCU_PLL_DIV 1

#define MCU_USB_DIV 2
/* 192 MHz */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 96 MHz */
#define F_CPU (F_PLL / 2)

/* TWI */
#define TWI_TIMEOUT_US_DEFAULT 10000

/* USB */
#define USB_CURRENT_MA 500

/* LEDs */
#define LED_ERROR_PIO PA17_PIO
#define LED_STATUS_PIO PB3_PIO

/* LED tape */
#define LEDTAPE_PIO PA8_PIO

/* Bump Sensor */
#define BUMPER_PIO PA21_PIO

/* Button */
#define SLEEP_BUTTON_PIO PA31_PIO

/* Low battery detect */
#define LOW_BATT_DETECT PA18_PIO

/* H-bridges */
#define H_SLEEP_PIO PB4_PIO
#define MA1_PIO PA7_PIO
#define MA2_PIO PA2_PIO
#define MB1_PIO PA0_PIO
#define MB2_PIO PA1_PIO

/* Radio  */
#define RADIO_CS_PIO PA11_PIO
#define RADIO_CE_PIO PA10_PIO
#define RADIO_IRQ_PIO PA24_PIO
#define RADIO_ENABLE_PIO PA9_PIO

/* Radio Channel Selector Headers */
#define RADIO_CH1 PA20_PIO
#define RADIO_CH2 PA23_PIO
#define RADIO_CH3 PA22_PIO
#define RADIO_CH4 PA19_PIO

#endif /* TARGET_H */
