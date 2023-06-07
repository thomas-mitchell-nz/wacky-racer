#include "pwm_handling.h"

/* Motor typedefs. */
static const pwm_cfg_t ma1_cfg =
{
    .pio = MA1_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 0),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};

static const pwm_cfg_t ma2_cfg =
{
    .pio = MA2_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 0),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};

static const pwm_cfg_t mb1_cfg =
{
    .pio = MB1_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 0),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};

static const pwm_cfg_t mb2_cfg =
{
    .pio = MB2_PIO,
    .period = PWM_PERIOD_DIVISOR (PWM_FREQ_HZ),
    .duty = PWM_DUTY_DIVISOR (PWM_FREQ_HZ, 0),
    .align = PWM_ALIGN_LEFT,
    .polarity = PWM_POLARITY_HIGH,
    .stop_state = PIO_OUTPUT_LOW
};

/* Initialise H-bridge and configure motors. */
void h_bridge_init (void) 
{
    /* Enable use of PB4 and PB5. */
    mcu_jtag_disable ();

    /* Enable H-Bridge. */
    pio_config_set (H_SLEEP_PIO, PIO_OUTPUT_HIGH);

    /* Initialise PWM on specified pin. */
    ma1 = pwm_init (&ma1_cfg);
    if (! ma1)
        panic (LED_ERROR_PIO, 1);

    ma2 = pwm_init (&ma2_cfg);
    if (! ma2)
        panic (LED_ERROR_PIO, 1);

    mb1 = pwm_init (&mb1_cfg);
    if (! mb1)
        panic (LED_ERROR_PIO, 1);

    mb2 = pwm_init (&mb2_cfg);
    if (! mb2)
        panic (LED_ERROR_PIO, 1);

    /* Start selected channels simultaneously. */
    pwm_channels_start (pwm_channel_mask (ma1) | pwm_channel_mask (ma2) \
        | pwm_channel_mask (mb1) | pwm_channel_mask (mb2));

    /* Set motors to stationary. */
    set_direction(STATIONARY);
}

/* Set motor duty cycles. */
void set_motor_duty_cycles (int ma1_duty, int ma2_duty, int mb1_duty, int mb2_duty)
{
    pwm_duty_ppt_set(ma1, ma1_duty);
    pwm_duty_ppt_set(ma2, ma2_duty);
    pwm_duty_ppt_set(mb1, mb1_duty);
    pwm_duty_ppt_set(mb2, mb2_duty);
}

/* Set motor duty from USB serial. */
void set_duty_from_serial (void) 
{
    char buf[256];
    /* Read a line from the specified stream. */
    if (fgets(buf, sizeof(buf), stdin)) {
        int num;
        char str[3];
        /* sscanf returns the number of input items successfully matched. */
        if (sscanf(buf, "%s %d", str, &num) == 2) {
            num = num > 100 ? 100 : num;
            num = num < 0 ? 0 : num;
            num = num * 10;

            /* Match input to motor and duty. */
            if (strcmp(str,"a1") == 0) {
                pwm_duty_ppt_set(ma1, num);
            } else if (strcmp(str,"a2") == 0) {
                pwm_duty_ppt_set(ma2, num);
            } else if (strcmp(str,"b1") == 0) {
                pwm_duty_ppt_set(mb1, num);
            } else if (strcmp(str,"b2") == 0) {
                pwm_duty_ppt_set(mb2, num);
            } else {
                printf("Specify motor and duty\n");
            }
        } else {
            printf("Invalid input\n");
        }
    }
}

/* Set car direction. */
void set_direction (int8_t command)
{   
    switch (command) {
        case STATIONARY:
            set_motor_duty_cycles (0,0,0,0);
            printf("STATIONARY\n");
            break;
        case FORWARD_SLOW_STRAIGHT:
            set_motor_duty_cycles (SLOW_SPEED,0,SLOW_SPEED,0);
            printf("FORWARD_SLOW_STRAIGHT\n");
            break;
        case FORWARD_SLOW_LEFT:
            set_motor_duty_cycles (TURN_SPEED,0,SLOW_SPEED,0);
            printf("FORWARD_SLOW_LEFT\n");
            break;
        case FORWARD_SLOW_RIGHT:
            set_motor_duty_cycles (SLOW_SPEED,0,TURN_SPEED,0);
            printf("FORWARD_SLOW_RIGHT\n");
            break;
        case FORWARD_FAST_STRAIGHT:
            set_motor_duty_cycles (FAST_SPEED,0,FAST_SPEED,0);
            printf("FORWARD_FAST_STRAIGHT\n");
            break;
        case FORWARD_FAST_LEFT:
            set_motor_duty_cycles (TURN_SPEED,0,SLOW_SPEED,0);
            printf("FORWARD_FAST_LEFT\n");
            break;
        case FORWARD_FAST_RIGHT:
            set_motor_duty_cycles (SLOW_SPEED,0,TURN_SPEED,0);
            printf("FORWARD_FAST_RIGHT\n");
            break;
        case BACKWARD_SLOW_STRAIGHT:
            set_motor_duty_cycles (0,SLOW_SPEED,0,SLOW_SPEED);
            printf("BACKWARD_SLOW_STRAIGHT\n");
            break;
        case BACKWARD_SLOW_LEFT:
            set_motor_duty_cycles (0,TURN_SPEED,0,SLOW_SPEED);
            printf("BACKWARD_SLOW_LEFT\n");
            break;
        case BACKWARD_SLOW_RIGHT:
            set_motor_duty_cycles (0,SLOW_SPEED,0,0);
            printf("BACKWARD_SLOW_RIGHT\n");
            break;
        case BACKWARD_FAST_STRAIGHT:
            set_motor_duty_cycles (0,FAST_SPEED,0,FAST_SPEED);
            printf("BACKWARD_FAST_STRAIGHT\n");
            break;
        case BACKWARD_FAST_LEFT:
            set_motor_duty_cycles (0,TURN_SPEED,0,SLOW_SPEED);
            printf("BACKWARD_FAST_LEFT\n");
            break;
        case BACKWARD_FAST_RIGHT:
            set_motor_duty_cycles (0,SLOW_SPEED,0,TURN_SPEED);
            printf("BACKWARD_FAST_RIGHT\n");
            break;
        default:
            set_motor_duty_cycles (0,0,0,0);
            printf("DEFAULT - STATIONARY\n");
            break;
    }
}