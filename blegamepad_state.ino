#include <BleGamepad.h>

BleGamepad bleGamepad;
long currentx, currenty;
byte currents;
byte x = 34, y = 35, s = 18;
bool lt = true, rt = true, ut = true, dt = true;
bool left = false, right = false, up = false, down = false;
long cyl = 0, cyr = 0;
volatile long li = 0;
void IRAM_ATTR pressed() {
  if (millis() - li > 400) {
    if (bleGamepad.isConnected()) {
      bleGamepad.press(BUTTON_1);
      //      Serial.println("pressed");
      bleGamepad.release(BUTTON_1);
      //      Serial.println("released");
    }
    li = millis();
  }

}
//void IRAM_ATTR released() {
//  if (bleGamepad.isConnected()) {
//
//  }
//}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleGamepad.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(18, INPUT_PULLUP);
  attachInterrupt(18, pressed, FALLING);
  //  attachInterrupt(18, released, RISING);
  analogReadResolution(10);

}

void loop() {
  if (bleGamepad.isConnected()) {
    digitalWrite(LED_BUILTIN, HIGH);
    //    //    bleGamepad.press(BUTTON_14);
    //    bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_CENTERED);
    currentx = analogRead(x);
    currenty = analogRead(y);
    currents = digitalRead(s);
    //      Serial.print(currentx);
    //      Serial.print("\t");
    //      Serial.println(currenty);

    if ( currenty > 900 && left == false ) {
      if (millis() - cyl < 210) {
        //        Serial.println("Esc");
        bleGamepad.press(BUTTON_2);
      } else {
        //        Serial.println("Left");
        bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_LEFT);
      }
      left = true;
      cyl = millis();
    } else if ( currenty < 700 && left == true ) {
      bleGamepad.release(BUTTON_2);
      bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_CENTERED);
      left = false;
      //release left
    }
    if ( currenty < 100 && right == false) {
      if (millis() - cyr < 200) {
        //tab mm
      } else {
        //right
        bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_RIGHT);
      }
      right = true;
    } else if (currenty > 300 && right == true) {
      bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_CENTERED);
      right = false;
      //release right
    }
    if ( currentx < 100 && up == false) {
      //up
      bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_UP);
      up = true;
    } else if ( currentx > 300 && up == true) {
      //release up
      bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_CENTERED);
      up = false;
    }
    if ( currentx > 900 && down == false) {
      //      Serial.println("Down");
      //down
      bleGamepad.press(BUTTON_4);
      bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_DOWN);
      down = true;
    } else if ( currentx < 700 && down == true) {
      //release down
      bleGamepad.setAxes(0, 0, 0, 0, 0, 0, DPAD_CENTERED);
      bleGamepad.release(BUTTON_4);
      down = false;
    }
    //    if (currents == LOW && lasts == HIGH ) {
    //
    //      //      Serial.println("Space");
    //      bleGamepad.press(BUTTON_1);
    //      delay(100);
    //      bleGamepad.release(BUTTON_1);
    //    }

  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
