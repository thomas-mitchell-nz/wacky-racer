#include <pio.h>
#include <stdlib.h>
#include "target.h"
#include "pacer.h"
#include "accelBuff.h"
#include "adxl345.h"
#include "usb_serial.h"
#include "ring.h"
#include "nrfHandling.h"
#include "delay.h"
#include "sounds.h"
#include "mcu_sleep.h"
#include "button.h"
#include "adc.h"
#include "irq.h"
#include "lowBatHandling.h"
#include "ledtape.h"
#include "ledTapeControl.h"

#define RW_SIZE 2

int16_t *average;


uint8_t command;
uint8_t prevCommand;
int8_t recievedCommand;

static const pio_t wakeUpPin = PA0_PIO;

int ledCounter;


usb_serial_cfg_t usb_serial_cfg =
    {
        .read_timeout_us = 10,
        .write_timeout_us = 10,
    };

usb_serial_t *usbSerial;

bool enterSleep;
bool exitSleep;

mcu_sleep_wakeup_cfg_t sleepWakeup; 
mcu_sleep_cfg_t sleepMode;
button_t sleepButton;

typedef enum {
    LOW_BAT_S,
    EXIT_LOW_BAT_S,
    ENTER_SLEEP_S,
    EXIT_SLEEP_S,
    OPERATION_S
} core_state_t;

typedef enum {
    TRANSMIT_S,
    RECIEVE_S,
    DISABLED_S
} op_state_t;


void configPIOs(void)
{
    pio_config_set (LED_STATUS_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LED_ERROR_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(RADIO_NRF_SLEEP, PIO_OUTPUT_HIGH);

    pio_config_set(RADIO_CH1, PIO_INPUT);
    pio_config_set(RADIO_CH2, PIO_INPUT);
    pio_config_set(RADIO_CH3, PIO_INPUT);
    pio_config_set(RADIO_CH4, PIO_INPUT);

    pio_config_set(BUZZER_PIO, PIO_OUTPUT_LOW);

    pio_config_set(PA26_PIO, PIO_OUTPUT_HIGH);

}

void configSleep(void)
{
    
    sleepWakeup.pio = wakeUpPin;
    sleepWakeup.active_high = false;

    sleepMode.mode = MCU_SLEEP_MODE_SLEEP;

    button_cfg_t sleepButtonCfg =
    {
        .pio = SLEEP_BUTTON_PIO
    };

    sleepButton = button_init(&sleepButtonCfg);
}   

void lowPowerEnable(void)
{
    // disable high power consumption devices
    pio_output_low(RADIO_NRF_SLEEP);
    usb_serial_shutdown(usbSerial);
}

void lowPowerDisable(void)
{
    // enable high power consumption devices
    pio_output_low(RADIO_NRF_SLEEP);
    usbSerial = usb_serial_init(&usb_serial_cfg, "/dev/usb_tty");
}

int
main (void)
{
    printf("\n\n\n\n\n");

    configPIOs();
    
    initAccel();
    nrfInit();
    pacer_init (100);
    // usb_serial_stdio_init ();
    initLowBatADC();
    configSleep();
    
    pio_output_high (LED_ERROR_PIO);

    char buffer[RADIO_PAYLOAD_SIZE + 1];

    bool sleepCooldown = false;
    bool lowBatStatus = false;

    usbSerial = usb_serial_init(&usb_serial_cfg, "/dev/usb_tty");
    if (usbSerial == 0) {
        pio_output_toggle(LED_ERROR_PIO);
    }

    int stateCounter = 0;
    int loopCounter = 0;
    int lowBatCounter = 0;
    ledCounter = 0;
    
    core_state_t coreState = OPERATION_S;
    op_state_t opState = TRANSMIT_S;

    // bumpSound();

    while (1)
    {    
        pacer_wait ();

        switch (coreState)
        {
            case LOW_BAT_S:
                (lowBatCounter >= 20) ? pio_output_toggle(LED_ERROR_PIO), lowBatCounter = 0 : lowBatCounter++;
                lowPowerEnable();
                pio_output_high(LED_STATUS_PIO);
                
                if (!getLowBatStatus()) {
                    coreState = EXIT_LOW_BAT_S;
                }

                break;

            case EXIT_LOW_BAT_S:

                pio_output_high(LED_ERROR_PIO);
                lowPowerDisable();
                coreState = OPERATION_S;
                break;
            
            case ENTER_SLEEP_S:
                coreState = EXIT_SLEEP_S;
                sleepCooldown = true;

                lowPowerEnable();
                
                mcu_sleep_wakeup_set(&sleepWakeup);
                delay_ms(100);
                mcu_sleep(&sleepMode);

                break;
            
            case EXIT_SLEEP_S:
                coreState = OPERATION_S;
                stateCounter = 0;
                
                lowPowerDisable();

                break;        
            
            case OPERATION_S:
                
                sampleADXL345();
                sampleLowBatADC();
                button_poll(sleepButton);

                if (prevCommand != command) {
                    updateLedTape(command);
                }

                (loopCounter >= 50) ? (loopCounter = 0, pio_output_toggle(LED_STATUS_PIO), sleepCooldown = false) : loopCounter++ ;
                (lowBatCounter >= 10) ? (lowBatCounter = 0, lowBatStatus = getLowBatStatus()) : lowBatCounter++;

                if (button_pushed_p(sleepButton) && !sleepCooldown) {
                    coreState = ENTER_SLEEP_S;  
                } 

                if (getLowBatStatus()) {
                    coreState = LOW_BAT_S;
                }


                switch(opState)
                {
                    case TRANSMIT_S:
                        average = getAverage();
                        // usb_serial_puts(usbSerial, "X:%d , Y:%d , Z:%d\n", average[0] , average[1] , average[2]);
                        prevCommand = command;
                        command = getCommand(average);  
                        nrfSendCommand(command); 
                        printCommand(usbSerial, command);
                        (stateCounter >= 10) ? opState = RECIEVE_S, stateCounter = 0: stateCounter++;
                        break;
                    case RECIEVE_S:
                        recievedCommand = nrdReadCommand();
                        (recievedCommand == 13) ? opState = DISABLED_S : ((stateCounter >= 5) ? opState = TRANSMIT_S, stateCounter = 0: stateCounter++);
                        break;
                    case DISABLED_S:
                        updateLedTape(100);
                        bumpSound();
                        // cleanBuffer();
                        // usb_serial_puts(usbSerial, "BUMPED\n");
                        updateLedTape(command);
                        opState = TRANSMIT_S;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }   
    }
}
