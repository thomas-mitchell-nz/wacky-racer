#include "lowBatHandling.h"

static adc_t batAdc;
static uint16_t ADC_data[1];
uint8_t lowBatCNT;
void initLowBatADC(void)
{
    adc_cfg_t bat_adc_cfg =
    {
        .bits = 12,
        .channels = BIT (BATTERY_ADC_CHANNEL),
        .trigger = ADC_TRIGGER_SW,
        .clock_speed_kHz = 1000
    };

    batAdc = adc_init (&bat_adc_cfg);
}

void sampleLowBatADC(void)
{
    adc_read (batAdc, ADC_data, sizeof (ADC_data));
}

bool getLowBatStatus(void)
{
    (ADC_data[0] <= LOW_BAT_THRESHOLD) ? (lowBatCNT++) : (lowBatCNT = 0);
    if (lowBatCNT >= LOW_BAT_SAMPLES) {
        return true;
    } 
    return false;
}

    

            
        