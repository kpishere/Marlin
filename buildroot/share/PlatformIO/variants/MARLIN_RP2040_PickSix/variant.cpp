#include "Arduino.h"
#include "pinDefinitions.h"

AnalogPinDescription g_AAnalogPinDescription[] = {
// Four ADC channel provided via i2c bus on virtual pins p46-p49
  { p46,        NULL },    // A0
  { p47,        NULL },    // A1
  { p48,        NULL },    // A2
  { p49,        NULL },    // A3
};

PinDescription g_APinDescription[] = {
  // D0 - D29, D30-D45 are extra GPIO via SPI bus
  { p0,  NULL, NULL, NULL },
  { p1,  NULL, NULL, NULL },
  { p2,  NULL, NULL, NULL },
  { p3,  NULL, NULL, NULL },
  { p4,  NULL, NULL, NULL },
  { p5,  NULL, NULL, NULL },
  { p6,  NULL, NULL, NULL },
  { p7,  NULL, NULL, NULL },
  { p8,  NULL, NULL, NULL },
  { p9,  NULL, NULL, NULL },
  { p10, NULL, NULL, NULL },
  { p11, NULL, NULL, NULL },
  { p12, NULL, NULL, NULL },
  { p13, NULL, NULL, NULL },
  { p14, NULL, NULL, NULL },
  { p15, NULL, NULL, NULL },
  { p16, NULL, NULL, NULL },
  { p17, NULL, NULL, NULL },
  { p18, NULL, NULL, NULL },
  { p19, NULL, NULL, NULL },
  { p20, NULL, NULL, NULL },
  { p21, NULL, NULL, NULL },
  { p22, NULL, NULL, NULL },
  { p23, NULL, NULL, NULL },
  { p24, NULL, NULL, NULL },
  { p25, NULL, NULL, NULL },
  { p26, NULL, NULL, NULL },
  { p27, NULL, NULL, NULL },
  { p28, NULL, NULL, NULL },
  { p29, NULL, NULL, NULL },
  { p30, NULL, NULL, NULL },
  { p31, NULL, NULL, NULL },
  { p32, NULL, NULL, NULL },
  { p33, NULL, NULL, NULL },
  { p34, NULL, NULL, NULL },
  { p35, NULL, NULL, NULL },
  { p36, NULL, NULL, NULL },
  { p37, NULL, NULL, NULL },
  { p38, NULL, NULL, NULL },
  { p39, NULL, NULL, NULL },
  { p40, NULL, NULL, NULL },
  { p41, NULL, NULL, NULL },
  { p42, NULL, NULL, NULL },
  { p43, NULL, NULL, NULL },
  { p44, NULL, NULL, NULL },
  { p45, NULL, NULL, NULL },
  { p46, NULL, NULL, NULL },
  { p47, NULL, NULL, NULL },
  { p48, NULL, NULL, NULL },
  { p49, NULL, NULL, NULL },
};

extern "C" {
  unsigned int PINCOUNT_fn() {
    return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
  }
}

#include "drivers/I2C.h"
#include "cardreader.h"

extern void exPinMode(pin_size_t pin, PinMode mode); 

void initVariant() {
}

#ifdef SERIAL_CDC

static void utox8(uint32_t val, uint8_t* s) {
  for (int i = 0; i < 16; i=i+2) {
    int d = val & 0XF;
    val = (val >> 4);

    s[15 - i -1] = d > 9 ? 'A' + d - 10 : '0' + d;
    s[15 - i] = '\0';
  }
}

extern "C" {
#include "hardware/flash.h"
#include "pico/bootrom.h"
}

uint8_t getUniqueSerialNumber(uint8_t* name) {
  uint32_t id[2];
  flash_get_unique_id((uint8_t*)&id[0]);
  utox8(id[0], &name[0]);
  utox8(id[1], &name[16]);
  return 32;
}

void _ontouch1200bps_() {
  reset_usb_boot(1 << digitalPinToPinName(LED_BUILTIN), 0);
}

#endif
