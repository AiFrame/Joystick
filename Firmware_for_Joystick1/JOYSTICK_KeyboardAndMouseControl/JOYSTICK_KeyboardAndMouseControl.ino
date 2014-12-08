
/*
  KeyboardAndMouseControl
 
 Controls the mouse from five pushbuttons on an Arduino Leonardo or Micro.
 
 Hardware:
 * 5 pushbuttons attached to D2, D3, D4, D5, D6
 
 
 The mouse movement is always relative. This sketch reads 
 four pushbuttons, and uses them to set the movement of the mouse.
 
 WARNING:  When you use the Mouse.move() command, the Arduino takes
 over your mouse!  Make sure you have control before you use the mouse commands.
 
 created 15 Mar 2012
 modified 27 Mar 2012
 by Tom Igoe
 
 this code is in the public domain
 
 */


const int switchPin = 2;      // switch to turn on and off mouse control
const int mouseButton = A0;    // input pin for the mouse pushButton
const int xAxis = A1;         // joystick X axis  
const int yAxis = A2;         // joystick Y axis
const int ledPin = 17;         // Mouse control LED 

// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range/4;      // resting threshold
int center = range/2;         // resting position value
boolean mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state
// set pin numbers for the five buttons:
 int MOTOR = 7;
 int PAD_UP = 11;
 int PAD_DOWN = 15;
 int PAD_LEFT = 14;
 int PAD_RIGHT = 16;
 
 int BUTTON_L1 = 3;
 int BUTTON_L2 = 2;
 int BUTTON_L3 = A5;
 int BUTTON_R1 = 4;
 int BUTTON_R2 = 12;
 int BUTTON_R3 = A0;
 
 int BUTTON_START = 5;
 int BUTTON_SELECT = 13;
 
 int BUTTON_TRIANGLE = 6;
 int BUTTON_SQUARE = 8;
 int BUTTON_CIRCLE = 10;
 int BUTTON_FORK = 9;
 int RX_Pin = A1;
 int RY_Pin = A2;
 int LX_Pin = A3;
 int LY_Pin = A4;

void setup() { // initialize the buttons' inputs:
  pinMode(MOTOR, OUTPUT);
  pinMode(PAD_UP, INPUT_PULLUP);
  pinMode(PAD_DOWN, INPUT_PULLUP);
  pinMode(PAD_LEFT, INPUT_PULLUP);
  pinMode(PAD_RIGHT, INPUT_PULLUP);
  
  pinMode(BUTTON_L1, INPUT_PULLUP);
  pinMode(BUTTON_L2, INPUT_PULLUP);
  pinMode(BUTTON_L3, INPUT_PULLUP);
  pinMode(BUTTON_R1, INPUT_PULLUP);
  pinMode(BUTTON_R2, INPUT_PULLUP);
  pinMode(BUTTON_R3, INPUT_PULLUP);
  
  pinMode(BUTTON_TRIANGLE, INPUT_PULLUP);
  pinMode(BUTTON_SQUARE, INPUT_PULLUP);
  pinMode(BUTTON_CIRCLE, INPUT_PULLUP);
  pinMode(BUTTON_FORK, INPUT_PULLUP);
  
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  
  pinMode(17, OUTPUT); 
  digitalWrite(MOTOR, LOW);
  
  Serial.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  // use serial input to control the mouse:
    // read the switch:
  int switchState = digitalRead(switchPin);
  // if it's changed and it's high, toggle the mouse state:
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      mouseIsActive = !mouseIsActive;
      // turn on LED to indicate mouse state:
      digitalWrite(ledPin, mouseIsActive);
    } 
  }
  // save switch state for next comparison:
  lastSwitchState = switchState;

  // read and scale the two axes:
  int xReading = readAxis(xAxis);
  int yReading = -readAxis(yAxis);

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    Mouse.move(xReading/1.2, yReading/1.2, 0);
  }  

  // read the mouse button and click or not click:
  // if the mouse button is pressed:
  if (digitalRead(mouseButton) == LOW) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT); 
    }
  } 
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT); 
    }
  }

  delay(responseDelay);

  // use the pushbuttons to control the keyboard:
  if (digitalRead(PAD_UP) == LOW) {
    Keyboard.write('w'); 
  }
  if (digitalRead(PAD_DOWN) == LOW) {
    Keyboard.write('s'); 
  }
  if (digitalRead(PAD_LEFT) == LOW) {
    Keyboard.write('a'); 
  }
  if (digitalRead(PAD_RIGHT) == LOW) {
    Keyboard.write('d'); 
  }
  if (digitalRead(BUTTON_TRIANGLE) == LOW) {
    Keyboard.write('1'); 
  }
  if (digitalRead(BUTTON_SQUARE) == LOW) {
    Keyboard.write('2'); 
  }
  if (digitalRead(BUTTON_CIRCLE) == LOW) {
    Keyboard.write('3'); 
  }
  if (digitalRead(BUTTON_FORK) == LOW) {
    Keyboard.write('q'); 
  }
  if (digitalRead(BUTTON_L1) == LOW) {
    Keyboard.write('A'); 
  }
  if (digitalRead(BUTTON_L2) == LOW) {
    Keyboard.write('s'); 
  }
  if (digitalRead(BUTTON_R1) == LOW) {
    Keyboard.write('d'); 
  }
  if (digitalRead(BUTTON_R2) == LOW) {
    Keyboard.write('f'); 
  }
  if (digitalRead(BUTTON_SELECT) == LOW) {
    Keyboard.write(177); 
  }
  if (digitalRead(BUTTON_START) == LOW) {
    Keyboard.write('w'); 
  }
  //delay(30);
}

int readAxis(int thisAxis) { 
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  } 

  // return the distance for this axis:
  return distance;
}
