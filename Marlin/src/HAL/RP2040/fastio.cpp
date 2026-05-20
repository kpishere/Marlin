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
#include "../platforms.h"

#ifdef __PLAT_RP2040__

#include "../../inc/MarlinConfig.h"

#if MOTHERBOARD == BOARD_RP2040_PICKSIX
#include <pins_arduino.h>
#include <pinDefinitions.h>
#include <SPI.h>
#include <Adafruit_SPIDevice.h>


// XRA1403 Register Addresses
/* XRA registers */
#define XRA_GSR   0x00 /* GPIO State - Read-Only (0x00)*/
#define XRA_OCR   0x04 /* Output Control - R/W (0x02) Ouptput value Hi/Lo */
#define XRA_PIR   0x08 /* Input Polarity Inversion - R/W (0x04)*/
#define XRA_GCR   0x0C /* GPIO Config - R/W (0x06) Hi = Input*/
#define XRA_PUR   0x10 /* Input Int Pull-up En/Dis - R/W (0x80) Lo = No Pullup*/
#define XRA_IER   0x14 /* Input Interrupt En. - R/W (0x0A) Hi = Enabled */
#define XRA_TSCR  0x18 /* Output Three-State Control - R/W (0x0C)*/
#define XRA_ISR   0x1C /* Input Interrupt Status - Read-Only (0x0E)*/
#define XRA_REIR  0x20 /* Input Rising Edge Interrupt Enable - R/W (0x10)*/
#define XRA_FEIR  0x24 /* Input Falling Edge Interrupt Enable - R/W (0x12)*/
#define XRA_IFR   0x28 /* Input Filter Enable/Disable - R/W (0x14)*/

#define XRA_READ 0x01
#define XRA_WRITE 0x00

#define XRA_OUTPUT 0x00
#define XRA_INPUT 0x01

#define XRA_INDISABLE 0x00
#define XRA_INENABLE 0x01

#define XRA_PULDIS 0x00
#define XRA_PULEN 0x01

struct egpio_msg {
    uint8_t cmd;
    uint8_t dat;
};

#define XRA_BANKS 2
struct egpio_cfg {
    uint8_t io; // 1 - input, 0 - output
    uint8_t pul; // 1 - pullup, 0 - none
    uint8_t ien; // 1 - enabled, 0 - none
    uint8_t val;
};

/* Bit for Pin */
#define XRA_BIT_PIN(pin) (0x01 << ((pin) % 8))

/* Return bank number from provided pin number P0-15
 */
#define XRA_PIN2BANK(pin) ((pin) > 7)

/* Update just one pin in data P0-15 */
#define XRA_SET_PIN(data,pin,val)  \
    (data) = ( ((val) & 0x01) ? (data) | (XRA_BIT_PIN(pin)) \
        : (data) & ~(XRA_BIT_PIN(pin)) )

/* Get value of just one pin in data P0-15 */
#define XRA_GET_PIN(data,pin) ((data) & (XRA_BIT_PIN(pin)))

/* Prepare packet for XRA - 16 bit
 *      rw: 0 - write, 1 - read
 *    bank: 0 - P0-1, 1 - P8-15
 * control: Command/control code - see enum XRA_CMD
 *    data: 8 bit / unsigned char
 */
#define XRA_MSG(rw, bank, control, data) \
    (((rw)==XRA_WRITE ? 0x00 : 0x80) | ((control) & 0x3C) \
        | ((bank)>0 ? 0x02 : 0x00)),(data)

/* Two byte message length with read16/write16
 */
#define XRA_MSG_SIZE 2
#define XRA_MSG_BITS 8

// Create SPI device instance
Adafruit_SPIDevice xra1403(XRA1403_CS_PIN, 
                          GPIO_SPI_SCLK1, 
                          GPIO_SPI_MISO1, 
                          GPIO_SPI_MOSI1);

// Shadow registers for SPI device
volatile struct egpio_cfg exp_bus[XRA_BANKS];

void xra_write(uint8_t bus, uint8_t reg, uint8_t data) {
    struct egpio_msg msg = {XRA_MSG(XRA_WRITE, bus, reg, data)};
    bool res = xra1403.write( (uint8_t *)&msg , XRA_MSG_SIZE );
}

uint8_t xra_read(uint8_t bus, uint8_t reg) {
    struct egpio_msg msg = {XRA_MSG(XRA_READ, bus, reg, 0x00)};
    xra1403.read((uint8_t *)&msg, XRA_MSG_SIZE);
    return (uint8_t)(msg.dat);
}

bool initializeXRA1403() {
    // Initialize the SPI device
    if (!xra1403.begin()) {
        return false;
    }
    // Initial state for gpio expansion - inputs, no pullup, no interrupt
    exp_bus[0].io  = exp_bus[1].io  = 0xff;
    exp_bus[0].pul = exp_bus[1].pul = 0x00;
    exp_bus[0].ien = exp_bus[1].ien = 0x00;
    exp_bus[0].val = exp_bus[1].val = 0x00;

    for(int i=0; i<XRA_BANKS; i++) {
        xra_write(i,XRA_GCR,exp_bus[i].io);
        xra_write(i,XRA_PUR,exp_bus[i].pul);
        xra_write(i,XRA_IER,exp_bus[i].ien);
        xra_write(i,XRA_OCR,exp_bus[i].val);
    }
    return true; // Initialization successful
}
#endif

void FastIO_init() {
#if MOTHERBOARD == BOARD_RP2040_PICKSIX
    initializeXRA1403();
#endif
}

#if MOTHERBOARD == BOARD_RP2040_PICKSIX
void exPinMode(PinName pin, PinMode mode) {
    pin_size_t idx = PinNameToIndex(pin);
    if( idx < NUM_DIGITAL_PINS ) {
        pinMode(pin,mode);
    } else {
        uint8_t xraPin = idx - NUM_DIGITAL_PINS;

        switch (mode) {
        case INPUT: // XRA_GCR
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].io,xraPin,1);
            xra_write(XRA_PIN2BANK(xraPin),XRA_GCR,exp_bus[XRA_PIN2BANK(xraPin)].io);
            break;
        case OUTPUT:
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].io,xraPin,0);
            xra_write(XRA_PIN2BANK(xraPin),XRA_GCR,exp_bus[XRA_PIN2BANK(xraPin)].io);
            break;
        case INPUT_PULLUP: // XRA_PUR
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].pul,xraPin,1);
            xra_write(XRA_PIN2BANK(xraPin),XRA_PUR,exp_bus[XRA_PIN2BANK(xraPin)].pul);
            break;
        case INPUT_PULLDOWN:
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].pul,xraPin,0);
            xra_write(XRA_PIN2BANK(xraPin),XRA_PUR,exp_bus[XRA_PIN2BANK(xraPin)].pul);
        default:
            break;
        }
    }
}
void exPinMode(pin_size_t pin, PinMode mode) {
    if( pin < NUM_DIGITAL_PINS ) {
        pinMode(pin,mode);
    } else {
        uint8_t xraPin = pin - NUM_DIGITAL_PINS;

        switch (mode) {
        case INPUT: // XRA_GCR
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].io,xraPin,1);
            xra_write(XRA_PIN2BANK(xraPin),XRA_GCR,exp_bus[XRA_PIN2BANK(xraPin)].io);
            break;
        case OUTPUT:
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].io,xraPin,0);
            xra_write(XRA_PIN2BANK(xraPin),XRA_GCR,exp_bus[XRA_PIN2BANK(xraPin)].io);
            break;
        case INPUT_PULLUP: // XRA_PUR
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].pul,xraPin,1);
            xra_write(XRA_PIN2BANK(xraPin),XRA_PUR,exp_bus[XRA_PIN2BANK(xraPin)].pul);
            break;
        case INPUT_PULLDOWN:
            XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].pul,xraPin,0);
            xra_write(XRA_PIN2BANK(xraPin),XRA_PUR,exp_bus[XRA_PIN2BANK(xraPin)].pul);
        default:
            break;
        }
    }
}

void exDigitalWrite(PinName pin, PinStatus val) {
    pin_size_t idx = PinNameToIndex(pin);
    if( idx < NUM_DIGITAL_PINS ) {
        digitalWrite(pin, val);
    } else {
        uint8_t xraPin = idx - NUM_DIGITAL_PINS;

        XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].val, xraPin,val);
        xra_write(XRA_PIN2BANK(xraPin), XRA_OCR, exp_bus[XRA_PIN2BANK(xraPin)].val);
    }
}
void exDigitalWrite(pin_size_t pin, PinStatus val) {
    if( pin < NUM_DIGITAL_PINS ) {
        digitalWrite(pin, val);
    } else {
        uint8_t xraPin = pin - NUM_DIGITAL_PINS;

        XRA_SET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].val, xraPin,val);
        xra_write(XRA_PIN2BANK(xraPin), XRA_OCR, exp_bus[XRA_PIN2BANK(xraPin)].val);
    }
}

PinStatus exDigitalRead(PinName pin) {
    pin_size_t idx = PinNameToIndex(pin);
    if( idx < NUM_DIGITAL_PINS ) {
        return digitalRead(pin);
    } else {
        uint8_t xraPin = idx - NUM_DIGITAL_PINS;
        exp_bus[XRA_PIN2BANK(xraPin)].val = xra_read(XRA_PIN2BANK(xraPin), XRA_GSR);

        //XRA_SET_PIN(mapped_bit,xraPin,1);
        //return !( exp_bus[XRA_PIN2BANK(xraPin)].val & mapped_bit );
        return (PinStatus)( XRA_GET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].val,xraPin) );
    }
}
PinStatus exDigitalRead(pin_size_t pin) {
    if( pin < NUM_DIGITAL_PINS ) {
        return digitalRead(pin);
    } else {
        uint8_t xraPin = pin - NUM_DIGITAL_PINS;
        exp_bus[XRA_PIN2BANK(xraPin)].val = xra_read(XRA_PIN2BANK(xraPin), XRA_GSR);

        //XRA_SET_PIN(mapped_bit,xraPin,1);
        //return !( exp_bus[XRA_PIN2BANK(xraPin)].val & mapped_bit );
        return (PinStatus)( XRA_GET_PIN(exp_bus[XRA_PIN2BANK(xraPin)].val,xraPin) );
    }
}

#endif // MOTHERBOARD == BOARD_RP2040_PICKSIX

#endif // __PLAT_RP2040__
