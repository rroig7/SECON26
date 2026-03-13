#include "start-off-strip.h"


// typedef enum {
//     OK                =  0,
//     ERR_BUS_FAIL      = -1,
//     ERR_ADDRESS_FAIL  = -2,
//     ERR_WRITE_FAIL    = -3,
//     ERR_READ_FAIL     = -4,
//     ERR_INVALID_ARG   = -5,
//     ERR_INIT_REQUIRED = -6
// } status_t;

status_t init_ldr(int gpio_handle, photoresistor_t *ph, int pin)
{
    if (ph == NULL)
        return ERR_BUS_FAIL;

    ph->gpio_handle = gpio_handle;
    ph->pin = pin;

    // Configure GPIO pin as input
    int rc = lgGpioClaimInput(gpio_handle, 0, pin);

    if (rc < 0)
        return ERR_BUS_FAIL;

    return OK;
}


status_t read_ldr(photoresistor_t *ph, int *value)
{
    if (ph == NULL || value == NULL) {
        printf("[ERROR] Initialize photoresistor and pass in value to store reading\n");
        return ERR_INIT_REQUIRED;
    }

    int reading = lgGpioRead(ph->gpio_handle, ph->pin);

    if (reading < 0)
        return ERR_READ_FAIL;

    *value = reading;

    return OK;
}

status_t calibrate_ldr(photoresistor_t *ph)
{
    if (ph == NULL)
        return ERR_INIT_REQUIRED;

    // For now, no calibration logic is needed to read
    // digital HIGH/LOW values from the GPIO pin.
    return OK;
}

status_t cleanup_ldr(photoresistor_t *ph)
{
    if (ph == NULL)
        return ERR_INIT_REQUIRED;

    ph->pin = 0;
    ph->gpio_handle = -1;

    return OK;
}