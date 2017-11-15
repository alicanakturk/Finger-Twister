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
int LEDB = 6;
int LEDC = 9;
int LEDD = 13;

int gameLevel = 0;

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

  Serial.println(gameLevel);
  playGame();

  //  Serial.println(trellis.isKeyPressed(LEDA));
  trellis.readSwitches();
  if(trellis.justReleased(LEDA) || trellis.justReleased(LEDB) || trellis.justReleased(LEDC) || trellis.justReleased(LEDD)){
      Serial.println("ERROR!");
      gameLevel = 0;
    }
  }

void playGame(){
  gameLevel = 1;
  trellis.setLED(LEDA);
  trellis.writeDisplay();

  if (trellis.readSwitches()){
      for (uint8_t i=0; i<numKeys; i++) {
      // if it was pressed, turn it on
        if (trellis.isKeyPressed(LEDA)) {
          lcd.clear();
          lcd.print("FIRST!");
          trellis.setLED(LEDB);
          trellis.writeDisplay();

          if (trellis.isKeyPressed(LEDA) && trellis.isKeyPressed(LEDB)){
            lcd.clear();
            lcd.print("SECOND!");
            trellis.setLED(LEDC);
            trellis.writeDisplay();

            if (trellis.isKeyPressed(LEDA) && trellis.isKeyPressed(LEDB) && trellis.isKeyPressed(LEDC)){
              lcd.clear();
              lcd.print("THIRD!");
              trellis.setLED(LEDD);
              trellis.writeDisplay();

              if (trellis.isKeyPressed(LEDA) && trellis.isKeyPressed(LEDB) && trellis.isKeyPressed(LEDC) && trellis.isKeyPressed(LEDD)){
                trellis.clrLED(LEDA);
                trellis.clrLED(LEDB);
                trellis.clrLED(LEDC);
                trellis.clrLED(LEDD);
                trellis.writeDisplay();
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
