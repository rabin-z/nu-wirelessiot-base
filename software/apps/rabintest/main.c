// Buttons app
//
// Use buttons and switches to control LEDs

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"

// Pin definitions
#include "nrf52840dk.h"

int main(void) {

  // Initialize.
  nrf_gpio_cfg_output(LED1);
  nrf_gpio_cfg_output(LED2);
  nrf_gpio_cfg_output(LED3);
  nrf_gpio_cfg_output(LED4);
  nrf_gpio_pin_set(LED1);
  nrf_gpio_pin_set(LED2);
  nrf_gpio_pin_set(LED3);
  nrf_gpio_pin_set(LED4);
  nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);
  
  typedef enum {b1, b2, b3, b4} blinking;
  
  blinking isblinking = b1;
  
  // Enter main loop.
  while (1) {
    
    if (!nrf_gpio_pin_read(BUTTON1)) {
      isblinking = b1;
    }
    if (!nrf_gpio_pin_read(BUTTON2)) {
      isblinking = b2;
    } 
    if (!nrf_gpio_pin_read(BUTTON3)) {
      isblinking = b3;
    } 
    if (!nrf_gpio_pin_read(BUTTON4)) {
      isblinking = b4;
    }
    
    if (isblinking == b1) {
      printf("b1\n");
      nrf_gpio_pin_toggle(LED1);
      nrf_gpio_pin_clear(LED2);
      nrf_gpio_pin_clear(LED3);
      nrf_gpio_pin_clear(LED4);
    } 
    if (isblinking == b2) {
      printf("b2\n");
      nrf_gpio_pin_toggle(LED2);
      nrf_gpio_pin_clear(LED1);
      nrf_gpio_pin_clear(LED3);
      nrf_gpio_pin_clear(LED4);
    } 
    if (isblinking == b3) {
      printf("b3\n");
      nrf_gpio_pin_toggle(LED3);
      nrf_gpio_pin_clear(LED2);
      nrf_gpio_pin_clear(LED1);
      nrf_gpio_pin_clear(LED4);
    } 
    if (isblinking == b4) {
      printf("b4\n");
      nrf_gpio_pin_toggle(LED4);
      nrf_gpio_pin_clear(LED2);
      nrf_gpio_pin_clear(LED3);
      nrf_gpio_pin_clear(LED1);
    }
    
    nrf_delay_ms(1000);

  }
}

