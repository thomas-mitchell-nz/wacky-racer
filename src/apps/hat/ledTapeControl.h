#ifndef LEDTAPECONTROL_H
#define LEDTAPECONTROL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pio.h>
#include "mcu.h"
#include "target.h"
#include "pacer.h"
#include "ledtape.h"
#include "nrfHandling.h"

#define NUM_LEDS 21

void updateLedTape(uint8_t command);

#endif /* LEDTAPECONTROL_H */