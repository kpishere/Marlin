/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2024 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "env_validate.h"

// TODO: https://www.arduinolibraries.info/libraries/adafruit-ads1x15

#define BOARD_INFO_NAME "RP2040 PickSix"
#define DEFAULT_MACHINE_NAME "RP2040 PickSix"

#ifndef MARLIN_EEPROM_SIZE
  #define MARLIN_EEPROM_SIZE             0x1000U  // 4K
#endif

///////////////////////////////////////////////////////////////
//  Virtual Input/Output of GPIO Expander XRA1403 on SPI bus 
///////////////////////////////////////////////////////////////
#define USE_XRA1403
//
// Limit Switches / Servos - 5V tolerant, 50mA sink/source unless noted
//
#define GPIO_DIAG1       30 // DIAG1 / TRG1 (Y endstop)  
#define GPIO_DIAG2       31 // DIAG2 / TRG2 (X endstop)  
#define GPIO_DIAG3       32 // DIAG3 / TRG3 (Z probe)    
#define GPIO_DIAG4       33 // DIAG4 / TRG4 -- Not Used -- 
#define GPIO_DIAG5       34 // DIAG5 / TRG5 (Fillament runout) 
#define GPIO_DIAG6       35 // -- Not Used -- 
#define GPIO_SERVO_P1    36 // AUX2-1 / CTL1 -- 300mA sink current as output
                            // (BEEPER)
#define GPIO_SEN1        37 // AUX2-5 / SEN1 (encoder 1) 
#define GPIO_SERVO_P2    38 // AUX2-2 / CTL2 -- 300mA sink current as output
                            // (P2 Click) 
#define GPIO_SEN2        39 // AUX2-7 / SEN2 (encoder 2) 
#define GPIO_SERVO_P3    40 // AUX2-6 / CTL3 -- 300mA sink current as output
                            // (Display a0) 
#define GPIO_SEN3        41 // AUX3-4 / SEN3 (card detect) 
//
// Servos / GPIO Output - 24V, 20A sink current
//
#define SERVO_HBED1      42 // HBED1
#define SERVO_HT1        43 // HT1 (extruder heat)  
#define SERVO_HT2        44 // HT2 (Hot End Fan & probe power)  
#define SERVO_HT3        45 // HT3 (Case light) 
//
//////////////////////////////////////////////////////////////

//
// Virtual pins of ads1x15 Chip on I2C bus
//
#define AIN0             46
#define AIN1             47
#define AIN2             48
#define AIN3             49

//
// Card Busses
//
#define GPIO_INT_CS10              0
#define GPIO_SPI_CS11              1
#define GPIO_SPI_SCLK1             2
#define GPIO_SPI_MOSI1             3
#define GPIO_SPI_MISO1             4
#define GPIO_SPI_CS10              5
#define GPIO_I2C_SDA1              6
#define GPIO_I2C_SCL1              7
#define SERIAL1_TX_PIN             8  // name used required by RP2040/MarlinSerial.cpp
#define SERIAL1_RX_PIN             9  // name used required by RP2040/MarlinSerial.cpp
#define SERIAL0_TX_PIN             12 // name used required by RP2040/MarlinSerial.cpp
#define SERIAL0_RX_PIN             13 // name used required by RP2040/MarlinSerial.cpp
#define GPIO_SPI_CS12_LCD          16

//
// GPIO expander
//
#define XRA1403_SPI_BUS            0  // SPI bus number if you have multiple
#define XRA1403_CS_PIN             GPIO_SPI_CS10
#define XRA1403_SPI_FREQ           1000000 // SPI frequency (1MHz is usually safe)

//
// Steppers
//
#define HW_LOW                 99 // Hard wired low
#define NC                     99 // not connected

#define Y_STOP_PIN                 GPIO_DIAG1
#define Y_STEP_PIN                 10
#define Y_DIR_PIN                  11
#define Y_ENABLE_PIN               HW_LOW
#ifndef Y_CS_PIN
  #define Y_CS_PIN                 NC
#endif

#define X_STOP_PIN                 GPIO_DIAG2
#define X_STEP_PIN                 14
#define X_DIR_PIN                  15
#define X_ENABLE_PIN               HW_LOW
#ifndef X_CS_PIN
  #define X_CS_PIN                 NC
#endif

#define Z_STOP_PIN                 GPIO_DIAG3
#define Z_STEP_PIN                 17
#define Z_DIR_PIN                  18
#define Z_ENABLE_PIN               HW_LOW
#ifndef Z_CS_PIN
  #define Z_CS_PIN                 NC
#endif

#define Z2_STEP_PIN                19
#define Z2_DIR_PIN                 20
#define Z2_ENABLE_PIN              HW_LOW
#ifndef Z2_CS_PIN
  #define Z2_CS_PIN                NC
#endif

#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN           GPIO_DIAG5
#endif

#define E0_STEP_PIN                21
#define E0_DIR_PIN                 22
#define E0_ENABLE_PIN              HW_LOW
#ifndef E0_CS_PIN
  #define E0_CS_PIN                NC
#endif

#define Z3_STEP_PIN                26
#define Z3_DIR_PIN                 27
#define Z3_ENABLE_PIN              HW_LOW
#ifndef Z3_CS_PIN
  #define Z3_CS_PIN                NC
#endif

// Misc.
#define LED_PIN                    25

// GPIO pin wired to MOSFET rated for 3A at jumper selectable 24/5/3.3V
#define GPIO_PWM0_PIN              28

//
// Temperature Sensors
//
#define TEMP_0_PIN                 AIN0  // Analog Input w. ADS1X1X in I2C bus
#define TEMP_BED_PIN               AIN1  // Analog Input w. ADS1X1X in I2C bus
#define TEMP_1_PIN                 AIN2  // Analog Input w. ADS1X1X in I2C bus
#define TEMP_2_PIN                 AIN3  // Analog Input w. ADS1X1X in I2C bus

#define TEMP_CHAMBER_PIN           TEMP_1_PIN

//
// Heaters / Fans
//
#define HEATER_0_PIN               SERVO_HT1
#define FAN0_PIN                   GPIO_PWM0_PIN  // PWM HW control
#define HEATER_BED_PIN             SERVO_HBED1

#if ENABLED(CASE_LIGHT_ENABLE) && !defined(CASE_LIGHT_PIN) && !defined(SPINDLE_LASER_ENA_PIN)
  #define CASE_LIGHT_PIN         SERVO_HT3  // Hardware PWM
#endif

/**
 * Default pins for TMC software SPI
 */
#if HAS_TMC_UART >= 1
  #define TMC_BAUD_RATE                115200
  #define TMC_USE_HW_SERIAL            1
  #define TMC_SW_UART 0  // Disable software serial
  #define TMC_USE_SW_UART 0 // Disable software UART
  #define HAS_TMC_UART 1    // Enable hardware UART
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  #define Y_HARDWARE_SERIAL  MarlinSerial0
  #define X_HARDWARE_SERIAL  MarlinSerial0
  #define Z_HARDWARE_SERIAL  MarlinSerial0
  #define Z2_HARDWARE_SERIAL MarlinSerial0
  #define E0_HARDWARE_SERIAL MarlinSerial1
  #define Z3_HARDWARE_SERIAL MarlinSerial1

  // Default TMC slave addresses - Serial0
  #ifndef Y_SLAVE_ADDRESS
    #define Y_SLAVE_ADDRESS                     0
    #define Y_SERIAL_TX_PIN                   SERIAL0_TX_PIN
    #define Y_SERIAL_RX_PIN                   SERIAL0_RX_PIN
  #endif
  #ifndef X_SLAVE_ADDRESS
    #define X_SLAVE_ADDRESS                     1
    #define X_SERIAL_TX_PIN                   SERIAL0_TX_PIN
    #define X_SERIAL_RX_PIN                   SERIAL0_RX_PIN
  #endif
  #ifndef Z_SLAVE_ADDRESS
    #define Z_SLAVE_ADDRESS                     2
    #define Z_SERIAL_TX_PIN                   SERIAL0_TX_PIN
    #define Z_SERIAL_RX_PIN                   SERIAL0_RX_PIN
  #endif
  #ifndef Z2_SLAVE_ADDRESS
    #define Z2_SLAVE_ADDRESS                    3
    #define Z2_SERIAL_TX_PIN                   SERIAL0_TX_PIN
    #define Z2_SERIAL_RX_PIN                   SERIAL0_RX_PIN
  #endif

  // Default TMC slave addresses - Serial1
  #ifndef E0_SLAVE_ADDRESS
    #define E0_SLAVE_ADDRESS                    0
    #define E0_SERIAL_TX_PIN                   SERIAL1_TX_PIN
    #define E0_SERIAL_RX_PIN                   SERIAL1_RX_PIN
  #endif
  #ifndef Z3_SLAVE_ADDRESS
    #define Z3_SLAVE_ADDRESS                    1
    #define Z3_SERIAL_TX_PIN                   SERIAL1_TX_PIN
    #define Z3_SERIAL_RX_PIN                   SERIAL1_RX_PIN
  #endif
#endif

//////////////////////////
// LCDs and Controllers //
//////////////////////////

#if ANY(TFT_COLOR_UI, TFT_CLASSIC_UI, TFT_LVGL_UI)

#elif HAS_WIRED_LCD

  //
  // LCD Display output pins
  //
  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)

  #elif ALL(IS_NEWPANEL, PANEL_ONE)

  #else

    #if ENABLED(CR10_STOCKDISPLAY)

    #elif ENABLED(ZONESTAR_LCD)

    #else

      #if ANY(MKS_12864OLED, MKS_12864OLED_SSD1306)
        #define LCD_PINS_DC                   25  // Set as output on init
        #define LCD_PINS_RS                   27  // Pull low for 1s to init
        // DOGM SPI LCD Support
        #define DOGLCD_CS                     16
        #define DOGLCD_MOSI                   17
        #define DOGLCD_SCK                    23
        #define DOGLCD_A0            LCD_PINS_DC
      #else
        // Not defined
      #endif

      #if !IS_NEWPANEL
        #define BEEPER_PIN                    SERVO_P1
      #endif

    #endif

    #if !IS_NEWPANEL
      // Buttons attached to a shift register
      // Not wired yet
      //#define SHIFT_CLK_PIN                 38
      //#define SHIFT_LD_PIN                  42
      //#define SHIFT_OUT_PIN                 40
      //#define SHIFT_EN_PIN                  17
    #endif

  #endif

  //
  // LCD Display input pins
  //
  #if IS_NEWPANEL

    #if ENABLED(REPRAP_DISCOUNT_SMART_CONTROLLER)

      #define BEEPER_PIN                      SERVO_P1

      #if ENABLED(CR10_STOCKDISPLAY)
        #define BTN_EN1                       17
        #define BTN_EN2                       23
      #else
        #define BTN_EN1                       31
        #define BTN_EN2                       33
      #endif

      #define BTN_ENC                         35
      #define SD_DETECT_PIN                   49
      #define KILL_PIN                        41

      #if ENABLED(BQ_LCD_SMART_CONTROLLER)
        #define LCD_BACKLIGHT_PIN             39
      #endif

    #elif ENABLED(REPRAPWORLD_GRAPHICAL_LCD)

      #define BTN_EN1                         64
      #define BTN_EN2                         59
      #define BTN_ENC                         63
      #define SD_DETECT_PIN                   42

    #elif ENABLED(LCD_I2C_PANELOLU2)

      #define BTN_EN1                         47
      #define BTN_EN2                         43
      #define BTN_ENC                         32
      #define LCD_SDSS_PIN             SD_SS_PIN
      #define KILL_PIN                        41

    #elif ENABLED(LCD_I2C_VIKI)

      #define BTN_EN1                         22  // https://files.panucatt.com/datasheets/viki_wiring_diagram.pdf explains 40/42.
      #define BTN_EN2                          7  // 22/7 are unused on RAMPS_14. 22 is unused and 7 the SERVO_HBED1 on RAMPS_13.
      #define BTN_ENC                         -1

      #define LCD_SDSS_PIN             SD_SS_PIN
      #define SD_DETECT_PIN                   49

    #elif ANY(VIKI2, miniVIKI)

      #define DOGLCD_CS                       45
      #define DOGLCD_A0                       44
      #define LCD_SCREEN_ROT_180

      #define BEEPER_PIN                      SERVO_P1
      #define STAT_LED_RED_PIN                32
      #define STAT_LED_BLUE_PIN               35

      #define BTN_EN1                         22
      #define BTN_EN2                          7
      #define BTN_ENC                         39

      #define SD_DETECT_PIN                   -1  // Pin 49 for display sd interface, 72 for easy adapter board
      #define KILL_PIN                        31

    #elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)

      #define DOGLCD_CS                       29
      #define DOGLCD_A0                       27

      #define BEEPER_PIN                      SERVO_P1
      #define LCD_BACKLIGHT_PIN               33

      #define BTN_EN1                         35
      #define BTN_EN2                         37
      #define BTN_ENC                         31

      #define LCD_SDSS_PIN             SD_SS_PIN
      #define SD_DETECT_PIN                   49
      #define KILL_PIN                        41

    #elif ENABLED(MKS_MINI_12864)

      #define DOGLCD_A0                       27
      #define DOGLCD_CS                       25

      // GLCD features
      // Uncomment screen orientation
      //#define LCD_SCREEN_ROT_90
      //#define LCD_SCREEN_ROT_180
      //#define LCD_SCREEN_ROT_270

      #define BEEPER_PIN                      SERVO_P1
      // not connected to a pin
      #define LCD_BACKLIGHT_PIN               65  // backlight LED on A11/D65

      #define BTN_EN1                         31
      #define BTN_EN2                         33
      #define BTN_ENC                         35

      #define SD_DETECT_PIN                   49
      #define KILL_PIN                        64

    #elif ENABLED(MINIPANEL)

      #define BEEPER_PIN                      SERVO_P1
      // not connected to a pin
      #define LCD_BACKLIGHT_PIN               65  // backlight LED on A11/D65

      #define DOGLCD_A0                       44
      #define DOGLCD_CS                       66

      // GLCD features
      // Uncomment screen orientation
      //#define LCD_SCREEN_ROT_90
      //#define LCD_SCREEN_ROT_180
      //#define LCD_SCREEN_ROT_270

      #define BTN_EN1                         40
      #define BTN_EN2                         63
      #define BTN_ENC                         59

      #define SD_DETECT_PIN                   49
      #define KILL_PIN                        64

    #elif ENABLED(ZONESTAR_LCD)

      #define ADC_KEYPAD_PIN                  12

    #elif ENABLED(AZSMZ_12864)

      #define BEEPER_PIN                       GPIO_SERVO_P1
      #define DOGLCD_A0                        GPIO_SERVO_P3
      #define DOGLCD_CS                        GPIO_SPI_CS12_LCD
      #define BTN_EN1                          GPIO_SEN1
      #define BTN_EN2                          GPIO_SEN2
      #define BTN_ENC                          GPIO_SERVO_P2
      #if !defined(SDCARD_CONNECTION) && DISABLED(NO_LCD_SDCARD)
        #define SDCARD_CONNECTION                LCD
      #endif
    #else

      // Beeper on AUX-4
      #define BEEPER_PIN                      SERVO_P1

      // Buttons are directly attached to AUX-2
      #if IS_RRW_KEYPAD
        #define SHIFT_OUT_PIN                 40
        #define SHIFT_CLK_PIN                 44
        #define SHIFT_LD_PIN                  42
        #define BTN_EN1                       64
        #define BTN_EN2                       59
        #define BTN_ENC                       63
      #elif ENABLED(PANEL_ONE)
        #define BTN_EN1                       59  // AUX2 PIN 3
        #define BTN_EN2                       63  // AUX2 PIN 4
        #define BTN_ENC                       49  // AUX3 PIN 7
      #else
        #define BTN_EN1                       37
        #define BTN_EN2                       35
        #define BTN_ENC                       31
        #define SD_DETECT_PIN                 41
      #endif

      #if ENABLED(G3D_PANEL)
        #define SD_DETECT_PIN                 49
        #define KILL_PIN                      41
      #endif
    #endif

    // CUSTOM SIMULATOR INPUTS
    #define BTN_BACK                          70

  #endif // IS_NEWPANEL

#endif // HAS_WIRED_LCD

#if SD_CONNECTION_IS(LCD)
  #define SD_SCK_PIN                       GPIO_SPI_SCLK1
  #define SD_MISO_PIN                      GPIO_SPI_MISO1
  #define SD_MOSI_PIN                      GPIO_SPI_MOSI1
  #define SD_SS_PIN                        GPIO_SPI_CS11
  #define SD_DETECT_PIN                    GPIO_SEN3
#elif SD_CONNECTION_IS(ONBOARD)
  #error "No onboard support for SD on this board."
#elif SD_CONNECTION_IS(CUSTOM_CABLE)
  #error "No custom SD drive cable defined for this board."
#endif
