// i dont actualy know how to program so dont expect this to be any good please
//
//Date: 9/08/23
//Wiring Instructions:
//  - Step one: don't
// 
//  - I am using a joystick module with it's own Z axis but you can replace it
//    with a regular push button if you want
//
//  - Wire Joycon Z or momentary push button between a Digital I/O pin.
//  - Wire Joycon X and Y pins into seperate Analog pins.
//  - Wire the joycon positive and ground pins into the arduino 5V and Ground pins
// 

const byte DEBUG = 1;  // Set to 1 to enable serial monitor debugging info

// --------CONSTANTS (won't change)---------------

//Joycon
const int Y_PIN = A0, X_PIN = A1; // Analog 
const byte Z_PIN = 13; // Digital
const byte DEADZONE = 150;

//Button
const byte BUTTON_PIN = 2; // Digital

//LED Strip
const byte LED_PIN = 12; // Digital
const byte NUM_LEDS = 30; // Number of lights in use

// ----------LIBRARIES--------------

#include "FastLED.h"
 CRGB leds[NUM_LEDS];

#include "JC_Button.h"
//------------ VARIABLES (will change)-----

byte direction = 0; 
//(8)(1)(2)
//(7)(0)(3)
//(6)(5)(4)

// ----------FUNCTIONS--------------
// these probably shouldn't go here....

  bool inCenterRange(int val) {
  return ((500 - DEADZONE <= val) && (val <= 500 + DEADZONE));
  }

  bool inUpperRange(int val) {
  return ((501 + DEADZONE <= val) && (val <= 1024));
  }
  
  bool inLowerRange(int val) {
  return ((0 <= val) && (val <= 499 - DEADZONE));
  }

//===============================================================================================

void setup() { 

  // input/output pin setups
  pinMode(LED_PIN, OUTPUT);
  pinMode(Z_PIN, INPUT); 

  // FastLED library specific setup
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  FastLED.clear();

  // Debugging for Serial monitor
  if(DEBUG) {
    Serial.begin(115200); //enable serial monitor
    Serial.println("Debugging has been enabled.");
  }
  Serial.println("Setup complete.");
}

//===============================================================================================

void loop() {
  buttonCheck();
}

//===============================================================================================

void buttonCheck(){

  // whystatic you ask???
  // i forgor

  static unsigned long time = 0, t0 = 0;
  static const long debounce = 100; // ms
  static int state = 0;

  int read = digitalRead(Z_PIN);

  switch(state) {
    case 0: // Reset. 
    if(read == HIGH){ // Proceeds when reading 5V (a potential button press)
      state = 1;
    }
    break;

    case 1: // Capture first time, immeadiatly proceed
    t0 = millis();
    state = 2;
    break;

    case 2:
    time = millis(); // Capture second time to compare with the first.
    if (time - t0 > debounce){ // Proceeds only if the debounce delay time has elapsed
      state = 3;
    }
    if(read == LOW){ // Resets if signal goes back to 0V before the debounce delay
      state = 0;
    }
    break;

    case 3: // Button has now confirmed a 'true' press
    if(read == LOW){ // But it will wait until the button is lifted before triggering the click event
      state = 4;
    }
    break;

    case 4: // Click
    // Event trigger
    if(DEBUG) {Serial.println("Click!");}
    joyconCalc();
    state = 0; // After running the events, resets
    break;

    default: if(DEBUG) {Serial.println("ERROR - Default case in buttonCheck switchcase");} // If I end up getting this message than I should probably start praying 
  }
}

// note: joyconCalc and directionTrigger could probably be merged...but I'm keeping some things seperate until I fully figure them out

void joyconCalc(){
  int y_axis = analogRead(Y_PIN); // 0-1024
  int x_axis = analogRead(X_PIN);

  if(DEBUG) { 
  Serial.print("Y Value: ");
  Serial.print(y_axis);
  Serial.print(" X Value: ");
  Serial.println(x_axis);
  }

  // evaluate by comparing the axises and change the direction variable accordingly
  if (inCenterRange(y_axis) && inCenterRange(x_axis)){
    direction = 0; // Center
  }
  else if (inUpperRange(y_axis) && inCenterRange(x_axis)){
    direction = 1; // North
  }
  else if (inUpperRange(y_axis) && inUpperRange(x_axis)){
    direction = 2; // NorthEast
  }
  else if (inCenterRange(y_axis) && inUpperRange(x_axis)){
    direction = 3; // East
  }
  else if (inLowerRange(y_axis) && inUpperRange(x_axis)){
    direction = 4; // SouthEast
  }
  else if (inLowerRange(y_axis) && inCenterRange(x_axis)){
    direction = 5; // South
  }
  else if (inLowerRange(y_axis) && inLowerRange(x_axis)){
    direction = 6; // SouthWest
  }
  else if (inCenterRange(y_axis) && inLowerRange(x_axis)){
    direction = 7; // West
  }
  else if (inUpperRange(y_axis) && inLowerRange(x_axis)){
    direction = 8; // NorthWest
  }
  else {
    direction = 9; // Let the people know that God can no longer save us
  }

  directionTrigger();

}

void directionTrigger(){
  // mostly placeholder stuff sorry
  switch (direction) {
  case 0:
  centerLED();
  if(DEBUG) {Serial.println("Center");}
    break;

  case 1:
    if(DEBUG) {Serial.println("North");}
    break;

  case 2:
    if(DEBUG) {Serial.println("NorthEast");}
    break;

  case 3:
    if(DEBUG) {Serial.println("East");}
    break;

  case 4:
    if(DEBUG) {Serial.println("SouthEast");}
    break;

  case 5:
    if(DEBUG) {Serial.println("South");}
    break;

  case 6:
    if(DEBUG) {Serial.println("SouthWest");}
    break;

  case 7:
    if(DEBUG) {Serial.println("West");}
    break;

  case 8:
    if(DEBUG) {Serial.println("NorthWest");}
    break;

  case 9:
  if(DEBUG) {Serial.println("ERROR - Case 9 directionPrint, Axises are not valid in printAndCalc");} // How did we get here...
  break;
  }
}

void centerLED(){
  // ignore this it's also a sort of placeholder
  // FastLED.clear();
  // fill_solid(leds, NUM_LEDS, CRGB::Red);
  // FastLED.show();
}