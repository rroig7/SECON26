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


status_t read_ldr(photoresistor_t *ph, unsigned long int *value)
{
    if (ph == NULL || value == NULL) {
        printf("[ERROR] Initialize photoresistor and pass in value to store reading\n");
        return ERR_INIT_REQUIRED;
    }

    unsigned long int count = 0;

    // Discharge capacitor
    lgGpioClaimOutput(ph->gpio_handle, 0, ph->pin, 0);
    usleep(10000);  // 10ms discharge

    // Switch to input and measure charge time
    lgGpioClaimInput(ph->gpio_handle, 0, ph->pin);
    while (lgGpioRead(ph->gpio_handle, ph->pin) == 0)
    {
        count++;
    }

    *value = count;

    return OK;
}



status_t calibrate_ldr(photoresistor_t *ph)
{
    if (ph == NULL)
        return ERR_INIT_REQUIRED;

    const int samples = 1000;
    unsigned long sum = 0;

    for (int i = 0; i < samples; i++) {
        unsigned long value;
        status_t rc = read_ldr(ph, &value);
        if (rc != OK) {
            printf("[ERROR] Failed to read LDR during calibration at sample %d\n", i);
            return rc;
        }
        sum += value;
    }

    double average = (double)sum / (double)samples;

    FILE *file = fopen(LDR_CALIBRATION_FILE, "w");
    if (file == NULL) {
        printf("[ERROR] Failed to open calibration file '%s' for writing\n", LDR_CALIBRATION_FILE);
        return ERR_WRITE_FAIL;
    }
    fprintf(file, "%f\n", average);
    fclose(file);

    printf("[LDR] Calibration complete. Average: %f (from %d samples), saved to %s\n",
           average, samples, LDR_CALIBRATION_FILE);

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