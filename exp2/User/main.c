#include <stdlib.h>
#include <stdio.h>
#include "LPC23xx.H"
#include "led.h"
#include "timer.h"


int main (void) {
    LED_Init();
    Timer_Init();
    
	while (1){
        ;
    }
}
