#include "start-off-strip.h"
#include <unistd.h>   // 500,000 microseconds = 0.5 seconds
#include <stdio.h>


int main(){

    int handle = lgGpiochipOpen(0);
    if (handle < 0) {
        printf("Failed to open GPIO chip\n");
        return ERR_BUS_FAIL;
    }

    photoresistor_t pt;
    init_ldr(handle ,&pt, LDR_PIN);
    // calibrate_ldr(&pt);
    unsigned long int ldr_reading = 0;
    read_ldr(&pt, &ldr_reading);

    while(1){
        read_ldr(&pt, &ldr_reading);
        printf("LDR Reading: %ld\n", ldr_reading);
        // printf("Baseline Reading: %f");
        // printf("Threshold Reading: %f");
        usleep(100000);
    }

    cleanup_ldr(&pt);
    return OK;
}