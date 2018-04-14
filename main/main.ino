/*

  Author: Jacob, Cassis, Perry, Marla, Garrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int colorR = 0;
int colorG = 0;
int colorB = 2005;

int led = 2;

int sensor1 = 1;
int sensor2 = 2;
int sensor3 = 3;

int val1 = 0;
int val2 = 0;
int val3 = 0;

boolean occupied1 = false;
boolean occupied2 = false;
boolean occupied3 = false;

int numSeats = 3;
int occupiedSeats = 0;
String[] failureMsgs;

void configureSensors(){
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
}

void readSensors(){
  val1 = analogRead(sensor1);
  val2 = analogRead(sensor2);
  val3 = analogRead(sensor3);
  delay(500);
}

void sendSerialData(){
  Serial.println(val1);
  Serial.println(val2);
  Serial.println(val3);
}

void doLogic(){
  if(val1 > 1020)
    occupied1 = !occupied1;
  if(val2 > 1020)
    occupied2 = !occupied2;
  if(val3 > 1020)
    occupied3 = !occupied3;
  if(val1
  
}

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    // Print a message to the LCD.
    lcd.print("Initializing...");
    configureSensors();
    pinMode(led, OUTPUT);
    Serial.begin(9600);
    delay(2000);
    lcd.clear();
}

void loop() 
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    readSensors();
    sendSerialData();
    doLogic();
    
    

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
