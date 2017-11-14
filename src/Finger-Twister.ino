#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

#define MOMENTARY 0
#define MODE MOMENTARY

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

#define numKeys (16)

int LEDA = 0;
int LEDB = 5;
int LEDC = 10;
int LEDD = 15;

// LEVEL1 = {1, 7, 11, 15}
// LEVEL2 = {3, 5, 9, 13}

void setup() {
  Serial.begin(9600);
  trellis.begin(0x70);

  lcd.begin(16,2);
  lcd.print("!FINGER TWISTER!");
  lcd.setCursor(0, 1);
  lcd.print("     LEVEL1");

  Serial.println("Finger Twister Demo");
  Serial.println("Level 1");

  startAnimation();

}

void loop() {
  delay(30);

  trellis.setLED(LEDA);
  trellis.writeDisplay();
  lcd.clear();
  lcd.print("FIRST FINGER");
  //
  // if (trellis.readSwitches()){
  //     for (uint8_t i=0; i<numKeys; i++) {
  //     // if it was pressed, turn it on
  //       if (trellis.justReleased(i)) {
  //         Serial.println("ERROR!!!");
  //     }
  //   }
  // }

//  Serial.println(trellis.isKeyPressed(LEDA));

  if (trellis.readSwitches()){
      for (uint8_t i=0; i<numKeys; i++) {
      // if it was pressed, turn it on
        if (trellis.isKeyPressed(LEDA)) {
          Serial.println("PRESS!");
          trellis.setLED(LEDB);
          trellis.writeDisplay();


          if (trellis.isKeyPressed(LEDA) && trellis.isKeyPressed(LEDB)){
            Serial.println("YES!");
            trellis.setLED(LEDC);
            trellis.writeDisplay();

            if (trellis.isKeyPressed(LEDA) && trellis.isKeyPressed(LEDB) && trellis.isKeyPressed(LEDC)){
              Serial.println("NEXT!");
              trellis.setLED(LEDD);
              trellis.writeDisplay();

              if (trellis.isKeyPressed(LEDA) && trellis.isKeyPressed(LEDB) && trellis.isKeyPressed(LEDC) && trellis.isKeyPressed(LEDD)){
                trellis.clrLED(LEDA);
                trellis.clrLED(LEDB);
                trellis.clrLED(LEDC);
                trellis.clrLED(LEDD);
                trellis.writeDisplay();
                delay(1000);
                startAnimation();

                //
                // delay(1000);
                // lcd.print("NEXT LEVEL!");
                // startAnimation();


              }
            }
          }
        }
      }
    }
}


void startAnimation(){
  // light up all the LEDs in order
  for (int i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(50);
    }
  // then turn them off
  for (int i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(50);

    }
  }
