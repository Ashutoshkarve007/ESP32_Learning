#include <DMD32.h>

/**********P10 pins************/
#define PIN_DMD_nOE 22
#define PIN_DMD_A 19  
#define PIN_DMD_B 21
#define PIN_DMD_CLK 18
#define PIN_DMD_SCLK  2
#define PIN_DMD_R_DATA  23
//******************************//
//+++++++++++Fonts+++++++++++//
#include "fonts/angka.h"
#include "fonts/angka_2.h"
#include "fonts/angka6x13.h"
#include "fonts/Arabic_tahoma.h"
#include "fonts/Arial_38b.h"
#include "fonts/Arial_black_16.h"
#include "fonts/Arial_Black_16_ISO_8859_1.h"
#include "fonts/Arial_Black21.h"
#include "fonts/Arial_Bold_14.h"
#include "fonts/Arial8.h"
#include "fonts/Arial9.h"
#include "fonts/Arial12.h"
#include "fonts/Arial14.h"
#include "fonts/ArialBlack20.h"
#include "fonts/ArialBlack22.h"
#include "fonts/ArialBlack24.h"
#include "fonts/ArialBlack36.h"
#include "fonts/BodoniMTBlack24.h"
#include "fonts/Comic24.h"
#include "fonts/Corsiva_12.h"
#include "fonts/DejaVuSans9.h"
#include "fonts/DejaVuSansItalic9.h"
#include "fonts/dictator.h"
#include "fonts/Droid_Sans_12.h"
#include "fonts/Droid_Sans_16.h"
#include "fonts/Droid_Sans_24.h"
#include "fonts/Droid_Sans_36.h"
#include "fonts/Droid_Sans_64.h"
#include "fonts/Droid_Sans_96.h"
#include "fonts/Droid_Sans_128.h"
#include "fonts/F04b.h"
#include "fonts/FIXEDNUMS7x15.h"
#include "fonts/fixednums15x31.h"
#include "fonts/fixednums15x31.h"
#include "fonts/FONT_7X6.h"
#include "fonts/Font3x5.h"
#include "fonts/huruf_kecilku.h"
#include "fonts/My32x15Font.h"
#include "fonts/MyBigFont.h"
#include "fonts/SYSTEM3x5.h"
#include "fonts/SystemFont5x7.h"
#include "fonts/Tahoma_32.h"
#include "fonts/Tiny.h"
#include "fonts/TomThumb.h"
#include "fonts/Verdana_digits_24.h"
#include "fonts/Webby.h"
//+++++++++++++++++++++++++++//
#define DISPLAYS_ACROSS 4
#define DISPLAYS_DOWN 2

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void hardwareTimer()
{
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  timer = timerBegin(0, cpuClock, true);
  timerAttachInterrupt(timer, &triggerScan, true);
  timerAlarmWrite(timer, 300, true);
  timerAlarmEnable(timer);
}

//***************************************************************************************************************************//
void setup(void)
{
  hardwareTimer();
  dmd.clearScreen( true );
}

void loop(void)
{


}
//***************************************************************************************************************************//
void fontTest()
{
  dmd.clearScreen( true );
  dmd.selectFont(angka);
  dmd.drawString(2,5,"angka",5, GRAPHICS_NORMAL);
}
void dmdTest()
{
  byte b;

  dmd.clearScreen( true );
//  dmd.selectFont(Arial_Black_16);
  dmd.drawChar(  0,  3, '2', GRAPHICS_NORMAL );
  dmd.drawChar(  7,  3, '3', GRAPHICS_NORMAL );
  dmd.drawChar( 17,  3, '4', GRAPHICS_NORMAL );
  dmd.drawChar( 25,  3, '5', GRAPHICS_NORMAL );
  dmd.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
  delay( 1000 );
  dmd.drawChar( 15,  3, ':', GRAPHICS_NOR    );   // clock colon overlay off
  delay( 1000 );
  dmd.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
  delay( 1000 );
  dmd.drawChar( 15,  3, ':', GRAPHICS_NOR    );   // clock colon overlay off
  delay( 1000 );
  dmd.drawChar( 15,  3, ':', GRAPHICS_OR     );   // clock colon overlay on
  delay( 1000 );

  dmd.drawMarquee("Scrolling Text", 14, (32 * DISPLAYS_ACROSS) - 1, 0);
  long start = millis();
  long timer = start;
  boolean ret = false;
  while (!ret) {
    if ((timer + 30) < millis()) {
      ret = dmd.stepMarquee(-1, 0);
      timer = millis();
    }
  }
  // half the pixels on
  dmd.drawTestPattern( PATTERN_ALT_0 );
  delay( 1000 );

  // the other half on
  dmd.drawTestPattern( PATTERN_ALT_1 );
  delay( 1000 );

  // display some text
  dmd.clearScreen( true );
  dmd.selectFont(System5x7);
  for (byte x = 0; x < DISPLAYS_ACROSS; x++) {
    for (byte y = 0; y < DISPLAYS_DOWN; y++) {
      dmd.drawString(  2 + (32 * x),  1 + (16 * y), "freet", 5, GRAPHICS_NORMAL );
      dmd.drawString(  2 + (32 * x),  9 + (16 * y), "ronic", 5, GRAPHICS_NORMAL );
    }
  }
  delay( 2000 );

  // draw a border rectangle around the outside of the display
  dmd.clearScreen( true );
  dmd.drawBox(  0,  0, (32 * DISPLAYS_ACROSS) - 1, (16 * DISPLAYS_DOWN) - 1, GRAPHICS_NORMAL );
  delay( 1000 );

  for (byte y = 0; y < DISPLAYS_DOWN; y++) {
    for (byte x = 0; x < DISPLAYS_ACROSS; x++) {
      // draw an X
      int ix = 32 * x;
      int iy = 16 * y;
      dmd.drawLine(  0 + ix,  0 + iy, 11 + ix, 15 + iy, GRAPHICS_NORMAL );
      dmd.drawLine(  0 + ix, 15 + iy, 11 + ix,  0 + iy, GRAPHICS_NORMAL );
      delay( 1000 );

      // draw a circle
      dmd.drawCircle( 16 + ix,  8 + iy,  5, GRAPHICS_NORMAL );
      delay( 1000 );

      // draw a filled box
      dmd.drawFilledBox( 24 + ix, 3 + iy, 29 + ix, 13 + iy, GRAPHICS_NORMAL );
      delay( 1000 );
    }
  }

  // stripe chaser
  for ( b = 0 ; b < 20 ; b++ )
  {
    dmd.drawTestPattern( (b & 1) + PATTERN_STRIPE_0 );
    delay( 200 );
  }
  delay( 200 );
}
