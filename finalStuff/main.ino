#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //LCD Pins

int buffer [512];
const int buzzPin = 8;
const int ledPin1 = 9;

void recordSample(byte num) {
  // put your main code here, to run repeatedly:
  for (byte j = 0; j < num; j++) {
    for (int i = 0; i < 512; i++) {
      buffer[i] = analogRead(A0);
    }
    for (int i = 0; i < 512; i++) {
      Serial.write(buffer[i]);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.write(0);
  ADCSRA = (ADCSRA & 0xf8) | 0x04;
  
  pinMode(buzzPin,OUTPUT);
    
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("Hello. I am");
  lcd.setCursor(0,1);
  lcd.print("Alexa");
  
  delay(2000);
  lcd.clear();
}

void loop() {
    int in = Serial.parseInt();
  if(in / 10 == 1){
    recordSample(in%10);
    return;
    }

  chooseCommand(in);
  
}
