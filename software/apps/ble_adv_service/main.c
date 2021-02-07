// BLE Service example app
//
// Creates a BLE service and blinks an LED

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "simple_ble.h"

#include "nrf52840dk.h"

// Intervals for advertising and connections
static simple_ble_config_t ble_config = {
  // c0:98:e5:4e:xx:xx
  .platform_id       = 0x4E,    // used as 4th octect in device BLE address
  .device_id         = 0xAABB,
  .adv_name          = "CS397/497", // used in advertisements if there is room
  .adv_interval      = MSEC_TO_UNITS(1000, UNIT_0_625_MS),
  .min_conn_interval = MSEC_TO_UNITS(500, UNIT_1_25_MS),
  .max_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
};

// read and notify service
static simple_ble_service_t readnotify_service = {{
  .uuid128 = {0x70,0x6C,0x98,0x41,0xCE,0x43,0x14,0xA9,
              0xB5,0x4D,0x22,0x2B,0x88,0x10,0xE6,0x32}
}};

static simple_ble_char_t readnotify_state_char = {.uuid16 = 0x1089}; // one more than above handle
static bool isblinking = false;
static bool isprinting = false;
int printnum = 0;

uint8_t button = 0x01;

/*******************************************************************************
 *   State for this application
 ******************************************************************************/
// Main application state
simple_ble_app_t* simple_ble_app;

void ble_evt_write(ble_evt_t const* p_ble_evt) {

  if (simple_ble_is_char_event(p_ble_evt, &readnotify_state_char)) {
    printf("Got write to characteristic!\n");

    isblinking = !isblinking;
    isprinting = !isprinting;
  }
}

int main(void) {

  printf("Board started. Initializing BLE: \n");

  // Setup LED GPIO
  nrf_gpio_cfg_output(LED1);
  nrf_gpio_cfg_output(LED2);
  
  nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

  // Setup BLE
  simple_ble_app = simple_ble_init(&ble_config);

  simple_ble_add_service(&readnotify_service);
      
  simple_ble_add_characteristic(1, 0, 1, 0, // read write notify vlen
      sizeof(button), (uint8_t*)&button,
      &readnotify_service, &readnotify_state_char);
      
  simple_ble_add_characteristic(1, 1, 0, 0, // read write notify vlen
      sizeof(isblinking), (uint8_t*)&isblinking,
      &readnotify_service, &readnotify_state_char);
      
  simple_ble_add_characteristic(1, 1, 0, 0, // read write notify vlen
      sizeof(isprinting), (uint8_t*)&isprinting,
      &readnotify_service, &readnotify_state_char);

  // Start Advertising
  simple_ble_adv_only_name();

  while(1) {
    if (!nrf_gpio_pin_read(BUTTON1)) {
      button = 0x01;
    }
    if (!nrf_gpio_pin_read(BUTTON2)) {
      button = 0x02;
    } 
    if (!nrf_gpio_pin_read(BUTTON3)) {
      button = 0x03;
    } 
    if (!nrf_gpio_pin_read(BUTTON4)) {
      button = 0x04;
    }
    
    simple_ble_notify_char(button);
  
    if (isblinking == true) {
      nrf_gpio_pin_toggle(LED2);
    }
    
    if (isprinting == true) {
      printf("printing %i\n", printnum);
      printnum++;
    }
    
    nrf_delay_ms(500);
  }
}

