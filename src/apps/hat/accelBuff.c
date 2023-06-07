/* File:   accelBuff.c
   Author: C. Price, T. Ponter-Amor, UC
   Date:   27 April 2023
   Descr:  Initialise and read from IMU (ADXL345)
*/
#include "accelBuff.h"

#ifndef ADXL345_ADDRESS
#error ADXL345_ADDRESS must be defined
#endif

ring_t imuBuffX;
ring_t imuBuffY;
ring_t imuBuffZ;

int16_t *intBuffX;
int16_t *intBuffY;
int16_t *intBuffZ;

adxl345_t *adxl345;
int16_t currentCoords[3];
int16_t total[3];
int16_t readOut[3];

int16_t *average;

static twi_cfg_t adxl345_twi_cfg =
{
    .channel = TWI_CHANNEL_0,
    .period = TWI_PERIOD_DIVISOR (100000), // 100 kHz
    .slave_addr = 0
};

/* Initialises ADXL345 */
void initAccel(void)
{
    twi_t adxl345_twi;

    adxl345_twi = twi_init (&adxl345_twi_cfg);

    adxl345 = adxl345_init (adxl345_twi, ADXL345_ADDRESS);

    intBuffX = malloc (MAX_BUFF);
    intBuffY = malloc (MAX_BUFF);
    intBuffZ = malloc (MAX_BUFF);

    average = malloc(6);

    ring_init (&imuBuffX, intBuffX, MAX_BUFF);
    ring_init (&imuBuffY, intBuffY, MAX_BUFF);
    ring_init (&imuBuffZ, intBuffZ, MAX_BUFF);

    for (int i=0; i<MAX_BUFF/2; i++) {

        adxl345_accel_read (adxl345, currentCoords);

        total[0] += currentCoords[0];
        total[1] += currentCoords[1];
        total[2] += currentCoords[2];

        ring_write(&imuBuffX, &(currentCoords[0]), RW_SIZE);
        ring_write(&imuBuffY, &(currentCoords[1]), RW_SIZE);
        ring_write(&imuBuffZ, &(currentCoords[2]), RW_SIZE);
    }
}

void cleanBuffer(void) 
{
    for (int i=0; i<MAX_BUFF/2; i++) {

        adxl345_accel_read (adxl345, currentCoords);

        total[0] += currentCoords[0];
        total[1] += currentCoords[1];
        total[2] += currentCoords[2];

        ring_write(&imuBuffX, &(currentCoords[0]), RW_SIZE);
        ring_write(&imuBuffY, &(currentCoords[1]), RW_SIZE);
        ring_write(&imuBuffZ, &(currentCoords[2]), RW_SIZE);
    }
}


/* Reads from ADXL345 and stores X, Y and Z values in an array of unsigned 16 bit integers
   Returns: 3 long array of unsigned 16 bit integers*/
void sampleADXL345(void)
{
    if (! adxl345_is_ready (adxl345)) {
        printf ("Waiting for accelerometer to be ready...\n");
    } else {
        adxl345_accel_read (adxl345, currentCoords);

        total[0] += currentCoords[0];
        total[1] += currentCoords[1];
        total[2] += currentCoords[2];

        ring_write(&imuBuffX, &(currentCoords[0]), RW_SIZE);
        ring_write(&imuBuffY, &(currentCoords[1]), RW_SIZE);
        ring_write(&imuBuffZ, &(currentCoords[2]), RW_SIZE);

        ring_read(&imuBuffX, &(readOut[0]), RW_SIZE);
        ring_read(&imuBuffY, &(readOut[1]), RW_SIZE);
        ring_read(&imuBuffZ, &(readOut[2]), RW_SIZE);

        total[0] -= readOut[0];
        total[1] -= readOut[1];
        total[2] -= readOut[2];
    }


    // printf("x: %5d, y: %5d, z: %5d\n", currentCoords[0], currentCoords[1], currentCoords[2]);
}

int16_t* getAverage(void)
{
    average[0] = total[0] / (MAX_BUFF/2);
    average[1] = total[1] / (MAX_BUFF/2);
    average[2] = total[2] / (MAX_BUFF/2);


    // printf("[X]: %d\n", average[0]);
    // printf("[Y]: %d\n", average[1]);
    // printf("[Z]: %d\n", average[2]);

    return average;
}