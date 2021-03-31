/*
  IM50175H 14-segment LCD library.
  T. Nakagawa

  Pin:
    1: +5V
    2: NC
    3: NC
    4: LATCH
    5: DATA
    6: CLOCK
    7: GND
*/

#include <Arduino.h>

class IM50175H {
public:
  IM50175H(uint8_t latch_pin, uint8_t data_pin, uint8_t clk_pin);
  void refresh(void);

  uint8_t buffer[8];

private:
  void send(uint8_t v);

  uint8_t latch_pin_;
  uint8_t data_pin_;
  uint8_t clock_pin_;
};
