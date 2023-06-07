#include "nrfHandling.h"

spi_cfg_t spi_cfg;
nrf24_cfg_t nrf24_cfg;

nrf24_t *nrf;

void nrfInit(void)
{
    delay_ms (100);
    uint8_t nrfChannel = getChannel();

    spi_cfg.channel = 0;
    spi_cfg.clock_speed_kHz = 1000;
    spi_cfg.cs = RADIO_CS_PIO;
    spi_cfg.mode = SPI_MODE_0;
    spi_cfg.cs_mode = SPI_CS_MODE_FRAME;
    spi_cfg.bits = 8;

    nrf24_cfg.channel = nrfChannel;
    nrf24_cfg.address = RADIO_ADDRESS;
    nrf24_cfg.payload_size = RADIO_PAYLOAD_SIZE;
    nrf24_cfg.ce_pio = RADIO_CE_PIO;
    nrf24_cfg.irq_pio = RADIO_IRQ_PIO;
    nrf24_cfg.spi = spi_cfg;

    nrf = nrf24_init (&nrf24_cfg);

    #ifdef RADIO_POWER_ENABLE_PIO
    // Enable radio regulator if present.
    pio_config_set (RADIO_POWER_ENABLE_PIO, PIO_OUTPUT_HIGH);
    delay_ms (10);
    #endif
}

uint8_t getChannel(void)
{
    if (pio_input_get(RADIO_CH1)) {
        return 1;
    } else if (pio_input_get(RADIO_CH2)) {
        return 9;
    } else if (pio_input_get(RADIO_CH3)) {
        return 97;
    } else if (pio_input_get(RADIO_CH4)) {
        return 4;
    } else {
        return 0;
    }
}

uint8_t getCommand(int16_t *average) 
{
    if (average[1] <= SLOW_THRESHOLD && average[1] >= -SLOW_THRESHOLD) {
        //car stationary
        return STATIONARY;
    } else {
        if (average[1] >= SLOW_THRESHOLD) {
            if (average[1] >= FAST_THRESHOLD) { 
                if (average[0] <= -SIDE_THRESHOLD) {
                    //forward fast left
                    return FORWARD_FAST_LEFT;
                } else if (average[0] >= SIDE_THRESHOLD) {
                    //forward fast right
                    return FORWARD_FAST_RIGHT;
                } else {
                    //forward fast
                    return FORWARD_FAST_STRAIGHT;
                }
            } else {
                if (average[0] <= -SIDE_THRESHOLD) {
                    //forward slow left
                    return FORWARD_SLOW_LEFT;
                } else if (average[0] >= SIDE_THRESHOLD) {
                    //forward slow right
                    return FORWARD_SLOW_RIGHT;
                } else {
                    //forward slow
                    return FORWARD_SLOW_STRAIGHT;
                }
            }
        } else if (average[1] <= -SLOW_THRESHOLD) {
            if (average[1] <= -FAST_THRESHOLD) {
                if (average[0] >= SIDE_THRESHOLD) {
                    //backward fast right
                    return BACKWARD_FAST_RIGHT;
                } else if (average[0] <= -SIDE_THRESHOLD) {
                    //backward fast left
                    return BACKWARD_FAST_LEFT;
                } else {
                    //backward fast
                    return BACKWARD_FAST_STRAIGHT;
                }
            } else {
                if (average[0] >= SIDE_THRESHOLD) {
                    //backward slow right
                    return BACKWARD_SLOW_RIGHT;
                } else if (average[0] <= -SIDE_THRESHOLD) {
                    //backward fast left
                    return BACKWARD_SLOW_LEFT;
                } else {
                    //backward slow
                    return BACKWARD_SLOW_STRAIGHT;
                }
            }
        }
    }

    // if (average[0] >= SIDE_THRESHOLD) {
    //     // Right Side
    //     if (average[1] >= SIDE_SLOW_THRESHOLD) {
    //         if (average[1] >= SIDE_FAST_THRESHOLD) {
    //             // Right Fast
    //             return FORWARD_FAST_RIGHT;
    //         } else {
    //             // Right Slow
    //             return FORWARD_SLOW_RIGHT;
    //         }
    //     } else if (average[1] <= -SIDE_SLOW_THRESHOLD) {
    //         if (average[1] <= -SIDE_FAST_THRESHOLD) {
    //             // Backward Right Fast
    //             return BACKWARD_FAST_RIGHT;
    //         } else {
    //             // Backward Right Slow
    //             return BACKWARD_SLOW_RIGHT;
    //         }
    //     } else {
    //         // Stationary
    //         return STATIONARY;
    //     }
    // } else if (average[0] <= -SIDE_THRESHOLD) {
    //     // Left Side
    //     if (average[1] >= SIDE_SLOW_THRESHOLD) {
    //         if (average[1] >= SIDE_FAST_THRESHOLD) {
    //             // Forward Left Fast
    //             return FORWARD_FAST_LEFT;
    //         } else {
    //             // Forward Left SLow
    //             return FORWARD_SLOW_LEFT;
    //         }
    //     } else if (average[1] <= -SIDE_SLOW_THRESHOLD) {
    //         if (average[1] <= -SIDE_FAST_THRESHOLD) {
    //             // Backward Left Fast
    //             return BACKWARD_FAST_LEFT;
    //         } else {
    //             // Backward Left SLow
    //             return BACKWARD_SLOW_LEFT;
    //         }
    //     } else {
    //         // Stationary
    //         return STATIONARY;
    //     }
    // } else {
    //     // Middle
    //     if (average[1] >= SLOW_THRESHOLD) {
    //         if (average[1] >= FAST_THRESHOLD) {
    //             // Forward Fast Straight
    //             return FORWARD_FAST_STRAIGHT;
    //         } else {
    //             // Forward Slow Straight
    //             return FORWARD_SLOW_STRAIGHT;
    //         }
    //     } else if (average[1] <= -SLOW_THRESHOLD) {
    //         if (average[1] <= -FAST_THRESHOLD) {
    //             // Backward Fast Straight
    //             return BACKWARD_FAST_STRAIGHT;
    //         } else {
    //             // Backward Slow Straigh
    //             return BACKWARD_SLOW_STRAIGHT;
    //         }
    //     } else {
    //         // Stationary
    //         return STATIONARY;
    //     }
    // }
    return STATIONARY;
}

void printCommand(usb_serial_t *usbSerial, int8_t currentCommand)
{
    // int8_t newCommand;
    switch(currentCommand) {
        case STATIONARY:
            usb_serial_puts(usbSerial, "STATIONARY\n");
            break;
        case FORWARD_SLOW_STRAIGHT:
            // printf("FORWARD_SLOW_STRAIGHT\n");
            usb_serial_puts(usbSerial, "FORWARD_SLOW_STRAIGHT\n");
            break;
        case FORWARD_SLOW_LEFT:
            // printf("FORWARD_SLOW_LEFT\n");
            usb_serial_puts(usbSerial, "FORWARD_SLOW_LEFT\n");
            break;
        case FORWARD_SLOW_RIGHT:
            usb_serial_puts(usbSerial, "FORWARD_SLOW_RIGHT\n");
            break;
        case FORWARD_FAST_STRAIGHT:
            usb_serial_puts(usbSerial, "FORWARD_FAST_STRAIGHT\n");
            break;
        case FORWARD_FAST_LEFT:
            usb_serial_puts(usbSerial, "FORWARD_FAST_LEFT\n");
            break;
        case FORWARD_FAST_RIGHT:
            usb_serial_puts(usbSerial, "FORWARD_FAST_RIGHT\n");
            break;
        case BACKWARD_SLOW_STRAIGHT:
            usb_serial_puts(usbSerial, "BACKWARD_SLOW_STRAIGHT\n");
            break;
        case BACKWARD_SLOW_LEFT:
            usb_serial_puts(usbSerial, "BACKWARD_SLOW_LEFT\n");
            break;
        case BACKWARD_SLOW_RIGHT:
            usb_serial_puts(usbSerial, "BACKWARD_SLOW_RIGHT\n");
            break;
        case BACKWARD_FAST_STRAIGHT:
            usb_serial_puts(usbSerial, "BACKWARD_FAST_STRAIGHT\n");
            break;
        case BACKWARD_FAST_LEFT:
            usb_serial_puts(usbSerial, "BACKWARD_FAST_LEFT\n");
            break;
        case BACKWARD_FAST_RIGHT:
            usb_serial_puts(usbSerial, "BACKWARD_FAST_RIGHT\n");
            break;
        default:
            usb_serial_puts(usbSerial, "INVALID COMMAND\n");
            break;
    }
}

// example data `010000` Start Bit (0) Forward (1) Slow (0) not left (0) not right (0) odd parity (0)

bool nrfSendCommand(uint8_t command)
{
    char buffer[RADIO_PAYLOAD_SIZE + 1];
    
    snprintf(buffer, sizeof(buffer), "%d", command);
    return nrf24_write (nrf, buffer, RADIO_PAYLOAD_SIZE);
    
}

int8_t nrdReadCommand(void) 
{
    /* Read command from radio. */
    static char buffer[RADIO_PAYLOAD_SIZE + 1];
    static uint8_t bytes;
    int8_t command = -1;

    bytes = nrf24_read (nrf, buffer, RADIO_PAYLOAD_SIZE);
    if (bytes != 0) {
        buffer[bytes] = 0;
        command = atoi(buffer);
    }

    return command;
}