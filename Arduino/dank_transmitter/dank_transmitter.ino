#define sensorpin A0

#include <VirtualWire.h>

void setup() {
  //Default tx pin (12) is used
  vw_setup(2000); //2000 bytes per second
}

/*
 * The receiver reads the analog value twice per second
 * from the sensor as an uint16_t and sends the raw
 * data through RF, as two uint8_t.
 */

void loop() {
  uint16_t readval = analogRead(sensorpin);
  uint8_t buf[2];
  readval &= 0x03FF; //analogRead gives 10 bits, mask to be sure
  buf[0] = (readval >> 8) & 0x00FF; //Store first byte in buf[0]
  buf[1] = (readval & 0x00FF); //Store second byte in buf[1]
  vw_send(buf, 2);
  delay(500);
}
