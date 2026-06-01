#pragma once
#include <macros.h>
#include <stdint.h>

#ifndef __PINS_ARDUINO__
#define __PINS_ARDUINO__

#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif

// Pin count
// ----
#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (30u)
#define NUM_ANALOG_INPUTS    (4u)
#define NUM_ANALOG_OUTPUTS   (0u)

extern PinName digitalPinToPinName(pin_size_t P);

// LEDs
// ----
#define PIN_LED     (25u)
#define LED_BUILTIN PIN_LED

// Analog pins - changed to virtulal pins of external ADC on i2c bus
// -----------
#define PIN_A0 (46u)
#define PIN_A1 (47u)
#define PIN_A2 (48u)
#define PIN_A3 (49u)

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;

#define ADC_RESOLUTION 12

// Serial
#define PIN_SERIAL_TX (8ul)  // Defined in pins_RP2040_PICKSIX.h Serial1
#define PIN_SERIAL_RX (9ul)  // Defined in pins_RP2040_PICKSIX.h Serial1

// SPI
#define PIN_SPI_MISO  (4u)  // Defined in pins_RP2040_PICKSIX.h
#define PIN_SPI_MOSI  (3u)  // Defined in pins_RP2040_PICKSIX.h
#define PIN_SPI_SCK   (2u)  // Defined in pins_RP2040_PICKSIX.h
#define PIN_SPI_SS    (16u) // defined in pins_RP2040_PICKSIX.h as GPIO_SPI_CS12_LCD
#define DOGLCD_CS     PIN_SPI_SS
#define DOGLCD_A0     40

//static const uint8_t SS   = PIN_SPI_SS;   // SPI Slave SS not used. Set here only for reference.
//static const uint8_t MOSI = PIN_SPI_MOSI;
//static const uint8_t MISO = PIN_SPI_MISO;
//static const uint8_t SCK  = PIN_SPI_SCK;

// Wire
#define PIN_WIRE_SDA        (6u)  // Defined in pins_RP2040_PICKSIX.h
#define PIN_WIRE_SCL        (7u)  // Defined in pins_RP2040_PICKSIX.h

#define SERIAL_HOWMANY		1
#define SERIAL1_TX			(digitalPinToPinName(PIN_SERIAL_TX))
#define SERIAL1_RX			(digitalPinToPinName(PIN_SERIAL_RX))

#define SERIAL_CDC			1
#define HAS_UNIQUE_ISERIAL_DESCRIPTOR
#define BOARD_VENDORID		0x2e8a
#define BOARD_PRODUCTID		0x00c0
#define BOARD_NAME			"RaspberryPi Pico"

uint8_t getUniqueSerialNumber(uint8_t* name);
void _ontouch1200bps_();

#define SPI_HOWMANY		(1)
#define SPI_MISO		(digitalPinToPinName(PIN_SPI_MISO))
#define SPI_MOSI		(digitalPinToPinName(PIN_SPI_MOSI))
#define SPI_SCK			(digitalPinToPinName(PIN_SPI_SCK))
#define SPI_SS			(digitalPinToPinName(PIN_SPI_SS))

#define WIRE_HOWMANY	(1)
#define I2C_SDA			(digitalPinToPinName(PIN_WIRE_SDA))
#define I2C_SCL			(digitalPinToPinName(PIN_WIRE_SCL))

#define digitalPinToPort(P)		(digitalPinToPinName(P)/32)

#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#define USB_MAX_POWER	(500)

#endif //__PINS_ARDUINO__
