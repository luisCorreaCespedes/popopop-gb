#include <gb/gb.h>
#include <stdio.h>

void main(void)
{
    // Print text before enter loop
    printf(" \nHello World!");
    printf(" \nPoPoPop!");

    // Turn display on
    DISPLAY_ON;

    // Loop forever
    while(1) {

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}