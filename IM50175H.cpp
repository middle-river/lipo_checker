/*
  IM50175H 14-segment LCD library.
  T. Nakagawa
*/

#include "IM50175H.h"

const static uint16_t tbl[] PROGMEM = {  // "0123456789 -.V"
  0b1110110100000000,
  0b0010100000000000,
  0b0110010100001001,
  0b0110110000001001,
  0b1010100000001001,
  0b1100110000001001,
  0b1100110100001001,
  0b1110100000000000,
  0b1110110100001001,
  0b1110110000001001,
  0b0000000000000000,
  0b0000000000001001,
  0b0000001000000000,
  0b1000000100100010,
};

IM50175H::IM50175H(uint8_t latch_pin, uint8_t data_pin, uint8_t clock_pin) : latch_pin_(latch_pin), data_pin_(data_pin), clock_pin_(clock_pin) {
  pinMode(latch_pin_, OUTPUT);
  pinMode(data_pin_, OUTPUT);
  pinMode(clock_pin_, OUTPUT);
}

void IM50175H::refresh(void) {
  /* 159-128 */
  for (uint8_t *p = buffer; p != buffer + 8; p++) {
    uint8_t tmp = (uint8_t)pgm_read_word(&tbl[*p]);
    send(tmp);
  }
  /* 127-120 */
  send(0x00);
  send(0x00);
  /* 119-88 */
  for (uint8_t *p = buffer + 7; p != buffer - 1; p--) {
    uint8_t tmp = (uint8_t)(pgm_read_word(&tbl[*p]) >> 4);
    send(tmp);
  }
  /* 87-80 */
  send(0x00);
  send(0x00);
  /* 79-48 */
  for (uint8_t *p = buffer; p != buffer + 8; p++) {
    uint8_t tmp = (uint8_t)(pgm_read_word(&tbl[*p]) >> 8);
    send(tmp);
  }
  /* 47-40 */
  send(0x00);
  send(0x00);
  /* 39-8 */
  for (uint8_t *p = buffer + 7; p != buffer - 1; p--) {
    uint8_t tmp = (uint8_t)(pgm_read_word(&tbl[*p]) >> 12);
    send(tmp);
  }
  /* 7-0 */
  send(0x00);
  send(0x00);
  /* Send LATCH */
  digitalWrite(latch_pin_, HIGH);
  digitalWrite(latch_pin_, LOW);
  return;
}

void IM50175H::send(uint8_t v) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(data_pin_, ((v & 0x01) != 0) ? HIGH : LOW);
    digitalWrite(clock_pin_, HIGH);
    digitalWrite(clock_pin_, LOW);
    v = (v >> 1);
  }
  return;
}
