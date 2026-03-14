
#include "../../core/robot-core.h"
#include <stdint.h>
#include <lgpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   // 500,000 microseconds = 0.5 seconds


#ifndef START_OFF_STRIP
#define START_OFF_STRIP

#define LDR_PIN 13
#define LDR_CALIBRATION_FILE "ldr_calibration"


// LEGEND (Short terms)
// ldr = light dependant resistor (photoresistor)


typedef struct{
    unsigned int pin;
    int gpio_handle;
} photoresistor_t;

status_t init_ldr(int gpio_handle, photoresistor_t *ph, int pin);
status_t read_ldr(photoresistor_t *ph, unsigned long int *value);
status_t calibrate_ldr(photoresistor_t *ph);
status_t cleanup_ldr(photoresistor_t *ph);

#endif // START_OFF_STRIP
