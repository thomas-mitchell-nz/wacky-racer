#ifndef NRF_HANDLING_H
#define NRF_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usb_serial.h"
#include "nrf24.h"
#include "delay.h"
#include "panic.h"
#include "spi.h"
#include "pio.h"

/* Radio macros. */
#define RADIO_ADDRESS       0x0123456788LL
#define RADIO_CHANNEL       3
#define RADIO_PAYLOAD_SIZE  4

/* Radio objects. */
spi_cfg_t spi_cfg;
nrf24_cfg_t nrf24_cfg;
nrf24_t *nrf;

/* Intitilise SPI and configure nRF. */
void nrf_init(void); 

/* Get channel from jumper channel select. */
uint8_t get_channel(void); 

/* Read command from radio. */
int8_t read_command(void); 

/* Send command via radio. */
bool send_command(uint8_t command); 

#endif /* NRF_HANDLING_H */