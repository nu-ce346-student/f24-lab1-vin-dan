#include "gpio.h"

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t _unused_A[(0x700-0x524)/4 - 1];
  uint32_t PIN_CNF[32];
} gpio_reg_t;

volatile gpio_reg_t* GPIO_REGS_P0 = (gpio_reg_t*)(0x50000504);
volatile gpio_reg_t* GPIO_REGS_P1 = (gpio_reg_t*)(0x50000804);

// Inputs:
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR

  uint8_t pin;
  // PORT 0:
  if (gpio_num <= 31) {
    pin = gpio_num;
    // if configuring this to an input: set dir = 0 and input = 0
    if (dir == GPIO_INPUT) {
      GPIO_REGS_P0->PIN_CNF[pin] |= (GPIO_INPUT << 0);
      GPIO_REGS_P0->PIN_CNF[pin] |= (GPIO_INPUT << 1);
    }
    // else set dir = 1 and input = 1
    else {
      GPIO_REGS_P0->PIN_CNF[pin] |= (GPIO_OUTPUT << 0);
      GPIO_REGS_P0->PIN_CNF[pin] |= (0 << 1);
    }
  }

  // PORT 1:
  else {
    pin = gpio_num - 32;
    // set rightmost bit to dir
    if (dir == GPIO_INPUT) {
      GPIO_REGS_P1->PIN_CNF[pin] |= (GPIO_INPUT << 0);
      GPIO_REGS_P1->PIN_CNF[pin] |= (GPIO_INPUT << 1);
    }
    // else set dir = 1 and input = 1
    else {
      GPIO_REGS_P1->PIN_CNF[pin] |= (GPIO_OUTPUT << 0);
      GPIO_REGS_P1->PIN_CNF[pin] |= (GPIO_OUTPUT << 1);
    }
  }
}

// Inputs:
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // This function should make the pin high
  // It can assume that the pin has already been configured
  uint8_t pin;
  // PORT 0:
  if (gpio_num <= 31) {
    pin = gpio_num;
    GPIO_REGS_P0->OUTSET |=  (1 << pin);
  }

  // PORT 1:
  else {
    pin = gpio_num - 32;
    GPIO_REGS_P1->OUTSET |=  (1 << pin);
  }
}

// Inputs:
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  uint8_t pin;
  // PORT 0:
  if (gpio_num <= 31) {
    pin = gpio_num;
    GPIO_REGS_P0->OUTCLR =  (1 << pin);
  }

  // PORT 1:
  else {
    pin = gpio_num - 32;
    GPIO_REGS_P1->OUTCLR =  (1 << pin);
  }
}

// Inputs:
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // This function should read the value from the pin
  // It can assume that the pin has already been configured
    uint8_t pin;
    uint32_t bit_mask; // 32 bits
    uint32_t pin_state;
  // PORT 0:
  if (gpio_num <= 31) {
    pin = gpio_num;
    bit_mask = (1 << pin);
    pin_state = (GPIO_REGS_P0->IN & bit_mask);
    return pin_state != 0;
  }

  // PORT 1:
  else {
    pin = gpio_num - 32;
    bit_mask = (1 << pin);
    pin_state = (GPIO_REGS_P0->IN & bit_mask);
    return pin_state != 0;
  }
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
  printf("\nout:\t");
  printf("%p", &GPIO_REGS_P1->OUT);
  printf("\ncnf9:\t");
  printf("%p", &GPIO_REGS_P1->PIN_CNF[9]);
  printf("\n");
}

