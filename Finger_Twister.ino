#include <Wire.h>
#include "Adafruit_Trellis.h"

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE MOMENTARY

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);
#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)

#define INTPIN A2


void setup() {
  Serial.begin(9600);
  Serial.println("Finger Twister Demo");

  trellis.begin(0x70);

  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);

      trellis.setLED(0);

  }
}


void loop() {
  delay(30);  
  
  if (MODE == MOMENTARY) {
  // If a button was just pressed or released...
  if (trellis.readSwitches()) {
    // go through every button
    for (uint8_t i=0; i<numKeys; i++) {
  // if it was pressed, turn it on
  if (trellis.justPressed(0)) {
    Serial.print("v"); Serial.println(i);
    trellis.setLED(6);
    trellis.setLED(0);

  if (trellis.readSwitches());
    trellis.setLED(11);

  }
  
  for (uint8_t i=0; i<numKeys; i++) {
  // if it was released, turn it off
  if (trellis.justReleased(i)) {
    Serial.print("^"); Serial.println(i);
    trellis.clrLED(i);
  }
  }
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }
    





}
