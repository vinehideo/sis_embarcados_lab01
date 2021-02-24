#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

void main(void){
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // LEDs D3 e D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);


  SysTickIntEnable();
  SysTickEnable();
  uint8_t LED_D4 = 0;

  while(1){
        time_t rawtime1,rawtime2;
        time( &rawtime1 );
        do
        {
          time( &rawtime2 );
        }
        while(difftime(rawtime2, rawtime1) < 1);
        if(LED_D4 == 1)
        {
          LED_D4 = 0;
        }
        else
        {
          LED_D4 = 1;
        }
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, LED_D4);
  } // while
} // main