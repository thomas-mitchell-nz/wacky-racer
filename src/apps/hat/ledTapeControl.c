#include "ledTapeControl.h"

uint8_t leds[23 * 3];
uint8_t redCoeff;
uint8_t blueCoeff;
uint8_t greenCoeff;

// backward = red, forward = green, stationary = blue
void updateLedTape(uint8_t command) {
    switch(command) {
        case STATIONARY:
            redCoeff = 0;
            redCoeff = 0;
            blueCoeff = 255;
            break;
        case FORWARD_SLOW_STRAIGHT:
            redCoeff = 0;
            greenCoeff = 127;
            blueCoeff = 0;
            break;
        case FORWARD_SLOW_LEFT:
            redCoeff = 0;
            greenCoeff = 127;
            blueCoeff = 0;
            break;
        case FORWARD_SLOW_RIGHT:
            redCoeff = 0;
            greenCoeff = 127;
            blueCoeff = 0;
            break;
        case FORWARD_FAST_STRAIGHT:
            redCoeff = 0;
            greenCoeff = 255;
            blueCoeff = 0;
            break;
        case FORWARD_FAST_LEFT:
            redCoeff = 0;
            greenCoeff = 255;
            blueCoeff = 0;
            break;
        case FORWARD_FAST_RIGHT:
            redCoeff = 0;
            greenCoeff = 255;
            blueCoeff = 0;
            break;
        case BACKWARD_SLOW_STRAIGHT:
            redCoeff = 127;
            greenCoeff = 0;
            blueCoeff = 0;
            break;
        case BACKWARD_SLOW_LEFT:
            redCoeff = 127;
            greenCoeff = 0;
            blueCoeff = 0;
            break;
        case BACKWARD_SLOW_RIGHT:
            redCoeff = 127;
            greenCoeff = 0;
            blueCoeff = 0;
            break;
        case BACKWARD_FAST_STRAIGHT:
            redCoeff = 255;
            greenCoeff = 0;
            blueCoeff = 0;
            break;
        case BACKWARD_FAST_LEFT:
            redCoeff = 255;
            greenCoeff = 0;
            blueCoeff = 0;
            break;
        case BACKWARD_FAST_RIGHT:
            redCoeff = 255;
            greenCoeff = 0;
            blueCoeff = 0;
            break;
        case 100:
            redCoeff = 255;
            greenCoeff = 0;
            blueCoeff =0;
        default:
            break;
    }

    for (int i = 0; i < NUM_LEDS; i++)
    {
        // Set full green  GRB order
        leds[i * 3] = greenCoeff;
        leds[i * 3 + 1] = redCoeff;
        leds[i * 3 + 2] = blueCoeff;
    }

    ledtape_write (LEDTAPE_PIO, leds, NUM_LEDS * 3);
}