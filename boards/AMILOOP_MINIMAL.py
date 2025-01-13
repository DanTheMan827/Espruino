#!/bin/false
# This file is part of Espruino, a JavaScript interpreter for Microcontrollers
#
# Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# ----------------------------------------------------------------------------------------
# This file contains information for a specific board - the available pins, and where LEDs,
# Buttons, and other in-built peripherals are. It is used to build documentation as well
# as various source and header files for Espruino.
# ----------------------------------------------------------------------------------------

import pinutils;

info = {
 'name' : "AmiiboLink",
 'boardname' : "AMIIBOLINK",
 'link' :  [ "https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52-DK" ],
 'default_console' : "EV_SERIAL1",
 'default_console_tx' : "D8",
 'default_console_rx' : "D6",
 'default_console_baudrate' : "9600",
 'variables' : 2630, # How many variables are allocated for Espruino to use. RAM will be overflowed if this number is too high and code won't compile.
 'bootloader' : 1,
 'binary_name' : 'espruino_%v_amiibolink.hex',
 'build' : {
   'optimizeflags' : '-Os',
   'libraries' : [
     'BLUETOOTH',
     #'NET',
     #'GRAPHICS',
     #'CRYPTO','SHA256','SHA512',
     #'AES',
     'NFC'
   ],
   'makefile' : [
     'DEFINES+=-DHAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND=1', # Looks like proper production nRF52s had this issue
     # 'DEFINES+=-DCONFIG_GPIO_AS_PINRESET', # reset isn't being used, so let's just have an extra IO (needed for Puck.js V2)
     #'DEFINES+=-DESPR_DCDC_ENABLE', # Ensure DCDC converter is enabled
     #'DEFINES += -DNEOPIXEL_SCK_PIN=22 -DNEOPIXEL_LRCK_PIN=16', # SCK pin needs defining as something unused for neopixel (HW errata means they can't be disabled) see https://github.com/espruino/Espruino/issues/2071
     'DEFINES += -DNRF_BLE_GATT_MAX_MTU_SIZE=53 -DNRF_BLE_MAX_MTU_SIZE=53', # increase MTU from default of 23
     'DEFINES += -DCENTRAL_LINK_COUNT=2 -DNRF_SDH_BLE_CENTRAL_LINK_COUNT=2', # allow two outgoing connections at once     
     'LDFLAGS += -Xlinker --defsym=LD_APP_RAM_BASE=0x3290', # set RAM base to match MTU=53 + CENTRAL_LINK_COUNT=2
     'DEFINES+=-DBLUETOOTH_NAME_PREFIX=\'"AmiLoop"\'',
     #'DEFINES+=-DCUSTOM_GETBATTERY=jswrap_puck_getBattery',
     'DEFINES+=-DNFC_DEFAULT_URL=\'"https://puck-js.com/go"\'',
     'DEFINES+=-DAPP_TIMER_OP_QUEUE_SIZE=3', # Puck.js magnetometer poll
     'DFU_PRIVATE_KEY=targets/nrf5x_dfu/dfu_private_key.pem',
     'DFU_SETTINGS=--application-version 0xff --hw-version 52 --sd-req 0x8C,0x91',
  ]
 }
};


chip = {
  'part' : "NRF52832",
  'family' : "NRF52",
  'package' : "QFN48",
  'ram' : 64,
  'flash' : 512,
  'speed' : 64,
  'usart' : 1,
  'spi' : 1,
  'i2c' : 1,
  'adc' : 1,
  'dac' : 0,
  'saved_code' : {
    'address' : ((118 - 21) * 4096), # Bootloader takes pages 120-127, FS takes 118-119
    'page_size' : 4096,
    'pages' : 21,
    'flash_available' : 512 - ((31 + 8 + 2 + 21)*4) # Softdevice uses 31 pages of flash, bootloader 8, FS 2, code 10. Each page is 4 kb.
  },
};

devices = {
  'BTN1' : { 'pin' : 'D13', 'pinstate' : 'IN_PULLDOWN' }, # Pin negated in software
  'LED1' : { 'pin' : 'D20' }, # Pin negated in software
  'LED2' : { 'pin' : 'D17' }, # Pin negated in software
  'SPEAKERA' : { 'pin' : 'D14' }, # Pin negated in software
  'NFC': { 'pin_a':'D9', 'pin_b':'D10' }
  # Pin D22 is used for clock when driving neopixels - as not specifying a pin seems to break things
};

# left-right, or top-bottom order
board = {};

def get_pins():
  pins = pinutils.generate_pins(0,31) # 32 General Purpose I/O Pins.
  pinutils.findpin(pins, "PD0", True)["functions"]["XL1"]=0;
  pinutils.findpin(pins, "PD1", True)["functions"]["XL2"]=0;
  pinutils.findpin(pins, "PD5", True)["functions"]["RTS"]=0;
  pinutils.findpin(pins, "PD6", True)["functions"]["TXD"]=0;
  pinutils.findpin(pins, "PD7", True)["functions"]["CTS"]=0;
  pinutils.findpin(pins, "PD8", True)["functions"]["RXD"]=0;
  pinutils.findpin(pins, "PD9", True)["functions"]["NFC1"]=0;
  pinutils.findpin(pins, "PD10", True)["functions"]["NFC2"]=0;
  pinutils.findpin(pins, "PD2", True)["functions"]["ADC1_IN0"]=0;
  pinutils.findpin(pins, "PD3", True)["functions"]["ADC1_IN1"]=0;
  pinutils.findpin(pins, "PD4", True)["functions"]["ADC1_IN2"]=0;
  pinutils.findpin(pins, "PD5", True)["functions"]["ADC1_IN3"]=0;
  pinutils.findpin(pins, "PD28", True)["functions"]["ADC1_IN4"]=0;
  pinutils.findpin(pins, "PD29", True)["functions"]["ADC1_IN5"]=0;
  pinutils.findpin(pins, "PD30", True)["functions"]["ADC1_IN6"]=0;
  pinutils.findpin(pins, "PD31", True)["functions"]["ADC1_IN7"]=0;
  
  # Make buttons and LEDs negated
  pinutils.findpin(pins, "PD13", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD17", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD20", True)["functions"]["NEGATED"]=0;

  # everything is non-5v tolerant
  for pin in pins:
    pin["functions"]["3.3"]=0;

  return pins
