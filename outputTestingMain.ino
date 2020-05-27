#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int settingsPin = 12;
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(settingsPin,INPUT);
  pinMode(ledPin,OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  
  delay(2000);
  lcd.clear();
  
}

unsigned int curState = 0;
const long loopInterval = 500;
unsigned long curTime;
unsigned long prevTime = 3000;

void loop() {
  curTime = millis();

  if(digitalRead(settingsPin) == HIGH)
    curState = 1;

  Serial.println("Current State: " + String(curState));

  if(curState == 1)
  {
    takeOnMe();
  }

  delay(100);
}
