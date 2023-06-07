#include "nrf_handling.h"

/* Intitilise SPI and configure nRF. */
void nrf_init(void)
{
    /* Configure channel select PIO. */
    pio_config_set(RADIO_CH1, PIO_INPUT);
    pio_config_set(RADIO_CH2, PIO_INPUT);
    pio_config_set(RADIO_CH3, PIO_INPUT);
    pio_config_set(RADIO_CH4, PIO_INPUT);

    /* Wait for pins to configure. */
    delay_ms(200);

    /* Get channel from jumper channel select. */
    uint8_t nrf_channel = get_channel();

    /* Enable radio regulator. */
    pio_config_set (RADIO_ENABLE_PIO, PIO_OUTPUT_HIGH);

    /* Configure SPI. */
    spi_cfg.channel = 0;
    spi_cfg.clock_speed_kHz = 1000;
    spi_cfg.cs = RADIO_CS_PIO;
    spi_cfg.mode = SPI_MODE_0;
    spi_cfg.cs_mode = SPI_CS_MODE_FRAME,
    spi_cfg.bits = 8;

    /* Configure nRF24. */
    nrf24_cfg.channel = nrf_channel;
    nrf24_cfg.address = RADIO_ADDRESS;
    nrf24_cfg.payload_size = RADIO_PAYLOAD_SIZE;
    nrf24_cfg.ce_pio = RADIO_CE_PIO;
    nrf24_cfg.irq_pio = RADIO_IRQ_PIO;
    nrf24_cfg.spi = spi_cfg;

    /* Initiliase nRF24. */
    nrf = nrf24_init (&nrf24_cfg);
    if (!nrf) panic (LED_ERROR_PIO, 2);
}

/* Get channel from jumper channel select. */
uint8_t get_channel(void)
{
    if (pio_input_get(RADIO_CH1)) {
        return 1;
    } else if (pio_input_get(RADIO_CH2)) {
        return 2;
    } else if (pio_input_get(RADIO_CH3)) {
        return 3;
    } else if (pio_input_get(RADIO_CH4)) {
        return 4;
    } else {
        return 0;
    }
}

/* Read command from radio. */
int8_t read_command(void) 
{
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

/* Send command via radio. */
bool send_command(uint8_t command) 
{
    char buffer[RADIO_PAYLOAD_SIZE + 1];
    
    snprintf(buffer, sizeof(buffer), "%d", command);
    
    return nrf24_write (nrf, buffer, RADIO_PAYLOAD_SIZE);
}