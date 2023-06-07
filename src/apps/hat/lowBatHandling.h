#ifndef LOWBATHANDLING_H
#define LOWBATHANDLING_H

#include "pio.h"
#include "target.h"
#include "adc.h"
#include "usb_serial.h"
#include <stdint.h>
#include <stdlib.h>
 
#define LOW_BAT_THRESHOLD 2500 // set to 2500 for under ~5V
#define LOW_BAT_SAMPLES 5

void initLowBatADC(void);

void sampleLowBatADC(void);

bool getLowBatStatus(void);

#endif /* LOWBATHANDLING_H */