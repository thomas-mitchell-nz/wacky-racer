#ifndef ACCELBUFF_H
#define ACCELBUFF_H

#include "pio.h"
#include "target.h"
#include "adxl345.h"
#include "usb_serial.h"
#include "ring.h"
#include <stdint.h>
#include <stdlib.h>

#define MAX_BUFF 20
#define RW_SIZE 2

void initAccel(void);

void cleanBuffer(void);

void sampleADXL345(void);

int16_t* getAverage(void);


#endif /* ACCELBUFF_H */