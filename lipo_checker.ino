// LiPo Checker.
// 2021-02-28  T. Nakagawa

#include "IM50175H.h"

#define LCD_PIN_LATCH PIN_PA6
#define LCD_PIN_DATA PIN_PA7
#define LCD_PIN_CLOCK PIN_PA1
#define ADC_PIN PIN_PA2

IM50175H lcd(LCD_PIN_LATCH, LCD_PIN_DATA, LCD_PIN_CLOCK);

void setup() {
  analogReference(INTERNAL4V34);
  analogReadResolution(10);
}

void loop() {
  uint32_t v = 0;	// [mV]
  for (int i = 0; i < 1024; i++) {
    v += analogRead(ADC_PIN);
  }
  // v = (v / 1024) * 4.34 / 1024 * 1000;
  v *= 4340;
  v >>= 20;

  lcd.buffer[7] = 13;	// V
  lcd.buffer[6] = 10;	// Space
  lcd.buffer[5] = (uint8_t)(v % 10);
  v /= 10;
  lcd.buffer[4] = (uint8_t)(v % 10);
  v /= 10;
  lcd.buffer[3] = (uint8_t)(v % 10);
  v /= 10;
  lcd.buffer[2] = 12;	// Period
  lcd.buffer[1] = (uint8_t)(v % 10);
  lcd.buffer[0] = 10;	// Space
  lcd.refresh();
}
