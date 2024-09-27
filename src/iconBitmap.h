
#include <avr/pgmspace.h>  

static const unsigned char PROGMEM bright[] = {
  0x1f, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x7f,
  0xff, 0xff, 0x00, 0xff, 0xf7, 0xff, 0x80, 0xf7, 0xf7,
  0xf7, 0x80, 0xfb, 0xf7, 0xef, 0x80, 0xfd, 0xf7, 0xdf,
  0x80, 0xfe, 0xff, 0xbf, 0x80, 0xff, 0xc1, 0xff, 0x80,
  0xff, 0xbe, 0xff, 0x80, 0xff, 0x7f, 0x7f, 0x80, 0xff,
  0x7f, 0x7f, 0x80, 0xe1, 0x7f, 0x43, 0x80, 0xff, 0x7f,
  0x7f, 0x80, 0xff, 0x7f, 0x7f, 0x80, 0xff, 0xbe, 0xff,
  0x80, 0xff, 0xc1, 0xff, 0x80, 0xfe, 0xff, 0xbf, 0x80,
  0xfd, 0xf7, 0xdf, 0x80, 0xfb, 0xf7, 0xef, 0x80, 0xf7,
  0xf7, 0xf7, 0x80, 0xff, 0xf7, 0xff, 0x80, 0xff, 0xff,
  0xff, 0x80, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff,
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xfc, 0x00
};
static const unsigned char PROGMEM temperature_ico[] = {
  0x1c,0x00,0x22,0x02,0x2b,0x05,0x2a,0x02,0x2b,0x38,0x2a,
  0x60,0x2b,0x40,0x2a,0x40,0x2a,0x60,0x49,0x38,0x9c,0x80,
  0xae,0x80,0xbe,0x80,0x9c,0x80,0x41,0x00,0x3e,0x00
  };
static const unsigned char PROGMEM humidity_ico[] = {
  0x04,0x00,0x04,0x00,0x0c,0x00,0x0a,0x00,0x12,0x00,0x11,
  0x00,0x20,0x80,0x20,0x80,0x41,0x40,0x40,0xc0,0x80,0xa0,
  0x80,0x20,0x40,0x40,0x40,0x40,0x30,0x80,0x0f,0x00
  };