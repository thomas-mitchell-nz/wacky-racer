/** @file   target.h
    @author M. P. Hayes, UCECE
    @date   12 February 2018
    @brief
*/
#ifndef TARGET_H
#define TARGET_H

#include "mat91lib.h"

/* This is for the carhat (chart) board configured as a hat!  */

/* System clocks  */
#define F_XTAL 12.00e6
#define MCU_PLL_MUL 16
#define MCU_PLL_DIV 1

#define MCU_USB_DIV 2
/* 192 MHz  */
#define F_PLL (F_XTAL / MCU_PLL_DIV * MCU_PLL_MUL)
/* 96 MHz  */
#define F_CPU (F_PLL / 2)

/* TWI  */
#define TWI_TIMEOUT_US_DEFAULT 10000
#define MPU_ADDRESS 0x68

/* USB  */
//#define USB_VBUS_PIO PA5_PIO
#define USB_CURRENT_MA 500

/* ADC  */
#define BATTERY_ADC_CHANNEL ADC_CHANNEL_7
#define ADC_1_CHANNEL ADC_CHANNEL_1
#define ADC_2_CHANNEL ADC_CHANNEL_6
#define ADC_3_CHANNEL ADC_CHANNEL_5
#define ADC_4_CHANNEL ADC_CHANNEL_4


/* IMU  */
#define IMU_INT_PIO PA0_PIO
#define ADXL345_ADDRESS 0x1D

/* LEDs  */
#define LED_ERROR_PIO PA2_PIO
#define LED_STATUS_PIO PA31_PIO
#define LED1_PIO PA31_PIO                        // Pin 52
#define LED2_PIO PA2_PIO                        // Pin 44

/* General  */
#define APPENDAGE_PIO PA1_PIO
#define SLEEP_PIO PA28_PIO

/* Buttons  */
#define SLEEP_BUTTON_PIO PA0_PIO // this pin wont work, rework button to PAO
#define WAKEUP_BUTTON_PIO PA0_PIO

/* Radio  */
#define RADIO_CS_PIO PA11_PIO
#define RADIO_CE_PIO PA10_PIO
#define RADIO_IRQ_PIO PA15_PIO
#define RADIO_NRF_SLEEP PA25_PIO

/* Radio Channel Selector Headers */
#define RADIO_CH1 PA20_PIO
#define RADIO_CH2 PA23_PIO
#define RADIO_CH3 PA22_PIO
#define RADIO_CH4 PA19_PIO

/* LED tape  */
#define LEDTAPE_PIO PA26_PIO

/* Piezzo Buzzer */
#define BUZZER_PIO PA30_PIO

#endif /* TARGET_H  */
