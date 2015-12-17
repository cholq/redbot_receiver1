#include <RedBot.h>

RedBotMotor motors;
RedBotSoftwareSerial XBee;

const byte maskFORWARD_RIGHT = B1;
const byte maskFORWARD_LEFT = B10;
const byte maskREVERSE_RIGHT = B100;
const byte maskREVERSE_LEFT = B1000;

bool bool_FwdR = false;
bool bool_FwdL = false;
bool bool_RevR = false;
bool bool_RevL = false;
byte data;
byte mask_out;

void setup() {
  XBee.begin(9600); 
  Serial.begin(19200);

  data = B0;

}

void loop() {
  

  if (XBee.available()) {
    data = XBee.read();
    
    /*Serial.print("data=");
    Serial.print(data);
    Serial.print(" BIN(");
    Serial.print(data, BIN);
    Serial.print(")  HEX(");
    Serial.print(data, HEX);
    Serial.println(")");*/
       
    mask_out = data & maskFORWARD_RIGHT;
    if (!(mask_out == 0)) {
      //Serial.println("found FwdR!");
      bool_FwdR = true;
    }
    else {
      bool_FwdR = false;
    }

    mask_out = data & maskFORWARD_LEFT;
    if (!(mask_out == 0)) {
      //Serial.println("found FwdL!");
      bool_FwdL = true;
    }
    else {
      bool_FwdL = false;
    }
    
    mask_out = data & maskREVERSE_RIGHT;
    if (!(mask_out == 0)) {
      //Serial.println("found RevR!");
      bool_RevR = true;
      bool_FwdR = false;
    }
    else {
      bool_RevR = false;
    }

    mask_out = data & maskREVERSE_LEFT;
    if (!(mask_out == 0)) {
      //Serial.println("found RevL!");
      bool_RevL = true;
      bool_FwdL = false;
    }
    else {
      bool_RevL = false;
    }
  }

  if ((bool_FwdR == false) && (bool_FwdL == false) && (bool_RevR == false) && (bool_RevL == false)) {
    motors.brake();
  }
  else {
    if (bool_FwdR == true) {
      motors.rightDrive(100);
    }
    if (bool_RevR == true) {
      motors.rightDrive(-100);
    }
    if (bool_FwdL == true) {
      motors.leftDrive(100);
    }
    if (bool_RevL == true) {
      motors.leftDrive(-100);
    }
  }
}
