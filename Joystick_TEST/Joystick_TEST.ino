/*
 Input Pullup Serial
 
 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a 
 digital input on pin 2 and prints the results to the serial monitor.
 
 The circuit: 
 * Momentary switch attached from pin 2 to ground 
 * Built-in LED on pin 13
 
 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal 
 20K-ohm resistor is pulled to 5V. This configuration causes the input to 
 read HIGH when the switch is open, and LOW when it is closed. 
 
 created 14 March 2012
 by Scott Fitzgerald
 
 http://www.arduino.cc/en/Tutorial/InputPullupSerial
 
 This example code is in the public domain
 
 */
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

void setup(){
  //start serial connection
  Serial.begin(9600);
  //configure pin2 as an input and enable the internal pull-up resistor
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
}

void loop(){
  //read the pushbutton value into a variable
  int sensorVal = !digitalRead(PAD_UP);
  sensorVal |= !digitalRead(PAD_DOWN);
  sensorVal |= !digitalRead(PAD_LEFT);
  sensorVal |= !digitalRead(PAD_RIGHT);
  sensorVal |= !digitalRead(BUTTON_L1);
  sensorVal |= !digitalRead(BUTTON_L2);
  sensorVal |= !digitalRead(BUTTON_L3);
  sensorVal |= !digitalRead(BUTTON_R1);
  sensorVal |= !digitalRead(BUTTON_R2);
  sensorVal |= !digitalRead(BUTTON_R3);
  sensorVal |= !digitalRead(BUTTON_TRIANGLE);
  sensorVal |= !digitalRead(BUTTON_SQUARE);
  sensorVal |= !digitalRead(BUTTON_CIRCLE);
  sensorVal |= !digitalRead(BUTTON_FORK);
  sensorVal |= !digitalRead(BUTTON_START);
  sensorVal |= !digitalRead(BUTTON_SELECT);
  //print out the value of the pushbutton
  
  //Serial.println(sensorVal);         

  // print the results to the serial monitor:
  Serial.print("RX_Value = " );                       
  Serial.print(map(analogRead(RX_Pin), 0, 1023, 0, 1023));      
  Serial.print(" RY_Value = ");      
  Serial.print(map(analogRead(RY_Pin), 0, 1023, 0, 1023)); 
  Serial.print(" LX_Value = " );                       
  Serial.print(map(analogRead(LX_Pin), 0, 1023, 0, 1023));      
  Serial.print(" LY_Value = ");      
  Serial.println(map(analogRead(LY_Pin), 0, 1023, 0, 1023)); 
  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the 
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(17, LOW);
    //digitalWrite(MOTOR, HIGH);
  } 
  else {
    digitalWrite(17, HIGH);
    //digitalWrite(MOTOR, LOW);
  }
  delay(10);
}



