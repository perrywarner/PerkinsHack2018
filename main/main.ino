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

boolean initialized = false;
int colorR;
int colorG;
int colorB;

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

int tableNum = 1;
int numSeats = 3;
int occupiedSeats = 0;
boolean isFull = false;
boolean isEmpty;

boolean fault = false;
String failureMsg = "Sensor N Failure";

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

void interpretData(){
  if(val1 > 1020){
    occupied1 = !occupied1;
  }
  else if(val1 > 100){
    failureMsg = "Sensor 1 Failure";
    fault = true;
  }
  else if(val2 > 1020){
    occupied2 = !occupied2;
  }
  else if(val2 > 100){
    failureMsg = "Sensor 2 Failure";
    fault = true;
  }
  else if(val3 > 1020){
    occupied3 = !occupied3;
  }
  else if(val3 > 100){
    failureMsg = "Sensor 3 Failure";
    fault = true;
  }
  else if(val1 < 100 && val2 < 100 && val3 < 100)
    fault = false;
  
  occupiedSeats = (int)occupied1 + (int)occupied2 + int(occupied3);
  if(occupiedSeats == numSeats){
    isFull = true;
    isEmpty = false;
  }
  else
    isFull = false;
  if(occupiedSeats > 0){
    isEmpty = false;
  }
  else if(occupiedSeats == 0){
    isEmpty = true;
  }
  Serial.println(fault);
}

void updateDisplay(){
  lcd.clear();
  if(fault){
    setupLcd(255, 0, 0);
    lcd.setCursor(0, 1);
    lcd.print(failureMsg);
  }
  else if(isFull){
    setupLcd(245, 160, 65);
    lcd.setCursor(0, 1);
    lcd.print("Table is Full");
  }
  else if(isEmpty){
    setupLcd(0, 255, 0);
    lcd.setCursor(0, 1);
    lcd.print("Table is Empty");
  }
  else
    setupLcd(0, 0, 255);
  lcd.setCursor(0, 0);
  lcd.print("Table ");
  lcd.print(tableNum);
  lcd.setCursor(10, 0);
  lcd.print(occupiedSeats);
  lcd.print("/");
  lcd.print(numSeats);
}

void setupLcd(int coloR, int coloG, int coloB){
  if(!initialized){
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    initialized = true;
  }
  lcd.setRGB(coloR, coloG, coloB);
}

void setup() 
{    
    setupLcd(0, 0, 255);
    // Print a message to the LCD.
    lcd.print("Initializing...");
    configureSensors();
    pinMode(led, OUTPUT);
    Serial.begin(9600);
    lcd.setCursor(0, 1);
    lcd.print("Please wait.");
    delay(2000);
    lcd.clear();
}

void loop() 
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    readSensors();
    sendSerialData();
    interpretData();
    updateDisplay();
    
    

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
