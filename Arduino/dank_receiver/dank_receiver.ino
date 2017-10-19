#define receiverPin A1

#include <LiquidCrystal.h>
#include <VirtualWire.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  vw_rx_start();
  vw_set_rx_pin(receiverPin);
  vw_set_tx_pin(A2);
  vw_set_ptt_pin(A3);
  vw_setup(2000); //2000 bytes per second
  
  lcd.begin(16, 2);
  lcd.clear();
}

/*
 * In this first implementation a singe uint16_t is
 * received by RF, split up into two uint8_t numbers.
 * This value contains the raw input data from the
 * moisture sensor, which is used to (arbitrarily)
 * display the current moisture level on the LCD.
 */

void loop() {
  uint8_t buf[2];
  uint8_t buflen = 2; 
  
  if(vw_get_message(buf, &buflen)) {
      lcd.clear();
      lcd.setCursor(0, 0);

      //Piece the bytes back to an uint16_t
      uint16_t readval = (buf[0] << 8) + buf[1];

      if (readval < 200) {
        lcd.print("FUKTIGT!!!");
      } else if (readval < 300) {
        lcd.print("Vatten OK!");
      } else if (readval < 500) {
        lcd.print("Ge mig vatten!");
      } else if (readval < 700) {
        lcd.print("VATTEN!!!");
      } else {
        lcd.print ("X_X");
      }
  }
}
