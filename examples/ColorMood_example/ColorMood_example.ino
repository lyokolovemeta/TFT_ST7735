#include <SPI.h>
#include <TFT_ST7735.h>



#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0


/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 the rest of pin below:
 */
#define __CS  10
#define __DC  6
#define __RST 23
/*
Teensy 3.x can use: 2,6,10,15,20,21,22,23
Arduino's 8 bit: any
DUE: check arduino site
If you do not use reset, tie it to +3V3
*/


TFT_ST7735 tft = TFT_ST7735(__CS, __DC, __RST);


float angle;

void setup()
{
  tft.begin();

}

// Translate a hue "angle" -120 to 120 degrees (ie -2PI/3 to 2PI/3) to
// a 6-bit R channel value
//
// This is very slow on a microcontroller, not a great example!
inline int angle_to_channel(float a) {
  if (a < -PI) a += 2 * PI;
  if (a < -2 * PI / 3  || a > 2 * PI / 3) return 0;
  float f_channel = cos(a * 3 / 4); // remap 120-degree 0-1.0 to 90 ??
  return ceil(f_channel * 255);//63
}

void loop() {
  uint16_t clr = (((angle_to_channel(angle - 4 * PI / 3) >> 1) & 0xF8) << 8) | (((angle_to_channel(angle - 2 * PI / 3)) & 0xFC) << 3) | ((angle_to_channel(angle) >> 1) >> 3);
  tft.fillScreen(clr);

  angle += 0.01;
  if (angle > PI)
    angle -= 2 * PI;
}