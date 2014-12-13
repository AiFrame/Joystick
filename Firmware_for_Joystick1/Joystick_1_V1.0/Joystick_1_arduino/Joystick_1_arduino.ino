/*
 * Copyright (c) 2014 by Sun Zebo <sun.zebo@gmail.com>
 * Servo controller library for maple.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
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
 int BUTTON_R3 = A2;
 
 int BUTTON_START = 5;
 int BUTTON_SELECT = 13;
 
 int BUTTON_TRIANGLE = 6;
 int BUTTON_SQUARE = 8;
 int BUTTON_CIRCLE = 9;
 int BUTTON_FORK = 10;
 int RX_Pin = A1;
 int RY_Pin = A0;
 int LY_Pin = A3;
 int LX_Pin = A4;

 byte buttons = 0;
 byte dPads = 0;
 
 int LAST_BUTTON_VALUE = 0;
 boolean NEW_BUTTON_STATE = 0;
 boolean LED_TRIG = 0;
 int RX_VALUE;
 int RY_VALUE;
 int LX_VALUE;
 int LY_VALUE;
 
void setup(){
  //start serial connection
  Serial.begin(115200);
  Serial1.begin(115200);
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
  
  bitWrite(buttons, 0, !digitalRead(BUTTON_SELECT)); //byte 1, bit 0
  bitWrite(buttons, 1, !digitalRead(BUTTON_START)); //byte , bit 1
  bitWrite(buttons, 2, !digitalRead(BUTTON_L1)); //byte 1, bit 2
  bitWrite(buttons, 3, !digitalRead(BUTTON_R1)); //byte 1, bit 3
  bitWrite(buttons, 4, !digitalRead(BUTTON_L2)); //byte 1, bit 4
  bitWrite(buttons, 5, !digitalRead(BUTTON_R2)); //byte 1, bit 5
  bitWrite(buttons, 6, !digitalRead(BUTTON_L3)); //byte 1, bit 6
  bitWrite(buttons, 7, !digitalRead(BUTTON_R3)); //byte 1, bit 7
  bitWrite(dPads, 0, !digitalRead(PAD_UP)); //byte 2, bit 0
  bitWrite(dPads, 1, !digitalRead(PAD_DOWN)); //byte 2, bit 1
  bitWrite(dPads, 2, !digitalRead(PAD_LEFT)); //byte 2, bit 2
  bitWrite(dPads, 3, !digitalRead(PAD_RIGHT)); //byte 2, bit 3
  bitWrite(dPads, 4, !digitalRead(BUTTON_TRIANGLE)); //byte 2, bit 4
  bitWrite(dPads, 5, !digitalRead(BUTTON_FORK)); //byte 2, bit 5
  bitWrite(dPads, 6, !digitalRead(BUTTON_SQUARE)); //byte 2, bit 6
  bitWrite(dPads, 7, !digitalRead(BUTTON_CIRCLE)); //byte 2, bit 7
  RX_VALUE = analogRead(RX_Pin);
  RY_VALUE = analogRead(RY_Pin);
  LX_VALUE = analogRead(LX_Pin);
  LY_VALUE = analogRead(LY_Pin);
  
  if ( dPads + buttons * 256 != LAST_BUTTON_VALUE )
  {
      NEW_BUTTON_STATE = true;
      LAST_BUTTON_VALUE = dPads + buttons * 256;
  }
  else 
  {
      NEW_BUTTON_STATE = false;
  }
  

  // print the results to the serial monitor:
  Serial.print("buttons = " );                       
  Serial.print(buttons);   
  Serial.print("dPads = " );                       
  Serial.print(dPads);   
  Serial.print("RX_Value = " );                       
  Serial.print(map(RX_VALUE, 0, 1023, 0, 1023));      
  Serial.print(" RY_Value = ");      
  Serial.print(map(RY_VALUE, 0, 1023, 0, 1023)); 
  Serial.print(" LX_Value = " );                       
  Serial.print(map(LX_VALUE, 0, 1023, 0, 1023));      
  Serial.print(" LY_Value = ");      
  Serial.println(map(LY_VALUE, 0, 1023, 0, 1023)); 

  if (NEW_BUTTON_STATE) {
    digitalWrite(17, LED_TRIG);
    //digitalWrite(MOTOR, HIGH);
    LED_TRIG = !LED_TRIG;
    if (buttons == 0 )
    {
        switch(dPads)
        {
            case 1://PAD_UP
                Serial1.println("EN1!");//up
            break;
            case 2://PAD_DOWN
                Serial1.println("EN2!");//down
            break;
            case 4://PAD_LEFT
                Serial1.println("EN3!");//left
            break;
            case 5://PAD_LEFT& PAD_UP
                Serial1.println("EN21!");//forward left
            break;
            case 6://PAD_LEFT& PAD_DOWN
                Serial1.println("EN23!");//back left
            break;
            case 8://PAD_RIGHT
                Serial1.println("EN4!");//right
            break;
            case 9://PAD_RIGHT&PAD_UP
                Serial1.println("EN22!");//forward right
            break;
            case 10://PAD_RIGHT&PAD_DOWN
                Serial1.println("EN24!");//back right
            break;
            case 16://BUTTON_TRIANGLE
                Serial1.println("EN14!");//stop
            break;
            case 32://BUTTON_FORK
                Serial1.println("EN13!");//Squat
            break;
            case 64://BUTTON_SQUARE
                Serial1.println("EN12!");//sword
            break;
            case 128://BUTTON_CIRCLE
                Serial1.println("EN11!");//fire
            break;
            case 36://BUTTON_FORK & PAD_LEFT
                Serial1.println("EN9!");//Down left
            break;
            case 40://BUTTON_FORK & PAD_RIGHT
                Serial1.println("EN10!");//Down right
            break;
            case 80://BUTTON_TRIANGLE & BUTTON_SQUARE
                Serial1.println("EN17!");//forward hit
            break;
            case 144://BUTTON_TRIANGLE & BUTTON_CIRCLE
                Serial1.println("EN18!");//back hit 
            break;
            default :
                Serial1.println("EN0!");
                delay(70);
            break;
        }
    }
    
    if (dPads == 0 )
    {
        switch(buttons)
        {
            case 1://SELECT
                Serial1.println("EN15!");//Back down
            break;
            case 2://START
                Serial1.println("EN16!");//face down
            break;
            case 4://L1
                Serial1.println("EN5!");//left turn
            break;
            case 8://R1
                Serial1.println("EN6!");//right turn
            break;
            case 16://L2
                Serial1.println("EN7!");//left hit
            break;
            case 20://L1+L2
                Serial1.println("EN19!");//left hit fast
            break;
            case 32://R2
                Serial1.println("EN8!");//right hit
            break;
            case 40://R1+R2
                Serial1.println("EN20!");//right hit fast
            break;
            case 64://L3
                Serial1.println("EN0!");//l3 stop and follow
            break;
            case 128://R3
                Serial1.println("EN0!");//r3 stop and follow
            break;
            case 192://L3+R3
                Serial1.println("EN0!");//l3 & r3 stop and follow
            break;
            default :
                Serial1.println("EN0!");
            break;
        }
    }
    
  } 

  else 
  {
      if (buttons == 64)//l3
      {
          Serial1.print("#25P");
          Serial1.print( map(LX_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#26P");
          Serial1.print( map(LY_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#27P");
          Serial1.print( map(RX_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#28P");
          Serial1.print( map(RY_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.println("T10!");
      }
      if (buttons == 128)//r3
      {
          Serial1.print("#5P");
          Serial1.print( map(RY_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#6P");
          Serial1.print( map(RX_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#7P");
          Serial1.print( map(LY_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#8P");
          Serial1.print( map(LX_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.println("T10!");
      }
      if (buttons == 192)//l3 & r3
      {
          Serial1.print("#5P");
          Serial1.print( map(RY_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#6P");
          Serial1.print( map(RX_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#7P");
          Serial1.print( map(LY_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#8P");
          Serial1.print( map(LX_VALUE,1023, 0, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#25P");
          Serial1.print( map(LX_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#26P");
          Serial1.print( map(LY_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#27P");
          Serial1.print( map(RX_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.print("#28P");
          Serial1.print( map(RY_VALUE,0, 1023, 2400,700),DEC); //prints left y thumbstick value
          Serial1.println("T10!");
      }
  }
  
  delay(70);
}


