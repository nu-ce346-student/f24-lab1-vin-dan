// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");

  // Turn on all LEDs on the back of the Microbit
  // Add code here

  // The Microphone LED is Port 0, Pin 20 and is active high
  // You will need to write to the DIR and OUT registers (in that order)

  // Write to the DIR register: set Pin 20 as output by
  *(uint32_t*)(0x50000514) |= (1 << 20);

  // Write to the OUT register: set Pin 20 high to turn on the LED
  *(uint32_t*)(0x50000504) |= (1 << 20);

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here

  // loop forever
  printf("Looping\n");
  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    gpio_print();
    nrf_delay_ms(100);
  }
}

