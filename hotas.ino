// CH Products Pro Throttle v1.0
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only. To USE the four buttons (non-hat) you
//       must bypass the internal diodes inside the throttle.
//       Before uploading, you must install the Joystick library from
//       https://github.com/MHeironimus/ArduinoJoystickLibrary
//
// by David Mc Anulty (dave000@hellspark.com)   10-15-2020
// based on JoystickButton.ino example by Matthew Heironimus 2015
//--------------------------------------------------------------------

#include <Joystick.h>
//Joystick_ Joystick;

//Setup Pro Throttle profile for Windows
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 20, 0,
  false, false, false, false, false, false,
  false, true, false, false, false);

// Serial debug, 0=off >0 on
const int debug=0;

// Pro throttle's Analog throttle 
const int throttlepin = A3;
int throttlevalue;

// Hats 1,2,3,4,buttons(left->right)
int hat[ ] = {2, 3, 4, 5, 6}; 

// Hat directions: Up, Left, Down, Right
int hatdirection[ ] = {7, 8, 9, 10};

void setup() {
  Serial.begin(9600); //Disable after debug
  
  // Analog pin the throttle is connected to
  pinMode(throttlepin, INPUT); 
     
  // Hat Direction input is detected by being pulled to ground by hat output (default HIGH)
  for (int i=0; i<4; i++) {
    pinMode(hatdirection[i], INPUT_PULLUP);
  }

  // Hat pulls hatdirection down to ground detect button presses (default HIGH)
  for (int i=0; i<5; i++) {
    pinMode(hat[i], OUTPUT);
    digitalWrite(hat[i], HIGH);
  }
  
  // Initialize Joystick Library to interface with computer
  Joystick.begin();
}


// Last state of the button
int hatButtonState[5][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

void loop() {
  // Read and send Pro Throttle's throttle value
  throttlevalue = analogRead(throttlepin);
  Joystick.setThrottle(throttlevalue);
  
  // Read throttle Hat values
  for (int hatindex=0; hatindex <5; hatindex++) {
    digitalWrite(hat[hatindex], LOW);
    for (int direction = 0; direction < 4; direction++) {
      int currentButtonState = !digitalRead(hatdirection[direction]);
      if (currentButtonState != hatButtonState[hatindex][direction]) {
        Joystick.setButton((hatindex*4)+direction, currentButtonState);
        hatButtonState[hatindex][direction] = currentButtonState;
      }
    }
    digitalWrite(hat[hatindex], HIGH);
  }



  // Debug stuff, disable when done testing
  if (debug > 0) {
    for(int j = 0; j < 5; j++) {
      Serial.print("Hat ");
      Serial.print(j);
      Serial.print(": ");
      for(int i = 0; i < 4; i++){
        Serial.print(hatButtonState[j][i]);
      }
      Serial.print(" ");
    }
    Serial.print("Throttle: ");
    Serial.print(throttlevalue);  
    Serial.println("");
  }

// Do we need a delay? I dunno?
delay(50);
}
