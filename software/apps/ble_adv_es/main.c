// BLE Advertisement Raw app
//
// Sends a BLE advertisement with raw bytes

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "simple_ble.h"

#include "nrf52840dk.h"

// Intervals for advertising and connections
static simple_ble_config_t ble_config = {
        // c0:98:e5:4e:xx:xx
        .platform_id       = 0x4E,   // used as 4th octect in device BLE address
        .device_id         = 0xAABB, // must be unique on each device you program!
        .adv_name          = "CS397/497", // used in advertisements if there is room
        .adv_interval      = MSEC_TO_UNITS(1000, UNIT_0_625_MS),
        .min_conn_interval = MSEC_TO_UNITS(500, UNIT_1_25_MS),
        .max_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
};

/*******************************************************************************
 *   State for this application
 ******************************************************************************/
// Main application state
simple_ble_app_t* simple_ble_app;


int main(void) {

  printf("Board started. Initializing BLE: \n");

  // Setup BLE
  // Note: simple BLE is our own library. You can find it in `nrf5x-base/lib/simple_ble/`
  simple_ble_app = simple_ble_init(&ble_config);

  // Start Advertising
  //uint8_t ble_data[BLE_GAP_ADV_SET_DATA_SIZE_MAX] = {0x02, 0x01, 0x06, 0x0A, 0x09, 0x52, 0x61, 0x62, 0x69, 0x6E, 0x5A, 0x68, 0x61, 0x6F, 0x02, 0xFF, 0x00, 0x00,};
  
  const char url_str[BLE_GAP_ADV_SET_DATA_SIZE_MAX] = { 'f', 'i', 'd', 'e', 'l', 'i', 't', 'y', '.', 'c', 'o', 'm',};
  
  simple_ble_es_with_name(url_str);

  //simple_ble_adv_raw(ble_data, 18);
  printf("Started BLE advertisements\n");

  while(1) {
    power_manage();
  }
}

