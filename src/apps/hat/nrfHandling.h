#ifndef NRFHANDLING_H
#define NRFHANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nrf24.h"
#include "pio.h"
#include "pacer.h"
#include "stdio.h"
#include "delay.h"
#include "usb_serial.h"

#define RADIO_ADDRESS 0x0123456788LL
#define RADIO_PAYLOAD_SIZE 4

#define SLOW_THRESHOLD 32
#define FAST_THRESHOLD 96
#define SIDE_THRESHOLD 72

#define SIDE_FAST_THRESHOLD 72
#define SIDE_SLOW_THRESHOLD 24


enum Commands {FORWARD_SLOW_STRAIGHT=0, FORWARD_SLOW_LEFT=1, FORWARD_SLOW_RIGHT=2, 
               FORWARD_FAST_STRAIGHT=3, FORWARD_FAST_LEFT=4, FORWARD_FAST_RIGHT=5,
               BACKWARD_SLOW_STRAIGHT=6, BACKWARD_SLOW_LEFT=7, BACKWARD_SLOW_RIGHT=8,
               BACKWARD_FAST_STRAIGHT=9, BACKWARD_FAST_LEFT=10, BACKWARD_FAST_RIGHT=11,
               STATIONARY=12};

void nrfInit(void);

uint8_t getChannel(void);

uint8_t getCommand(int16_t *average);

void printCommand(usb_serial_t *usbSerial, int8_t currentCommand);

bool nrfSendCommand(uint8_t command);

int8_t nrdReadCommand(void);

#endif /* NRFHANDLING_H */