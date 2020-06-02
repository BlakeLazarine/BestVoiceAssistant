void offAll()
{
  digitalWrite(redLedPin,LOW);
  digitalWrite(blueLedPin,LOW);
  digitalWrite(greenLedPin,LOW);
}

void lightShow()
{
  offAll();
  delay(1000);

  analogWrite(redLedPin,75);
  delay(300);
  analogWrite(blueLedPin,125);
  delay(300);
  analogWrite(greenLedPin,175);
  delay(300);

  offAll();

  for(int i = 30; i < 225; i+=12)
  {
    analogWrite(redLedPin,i);
    delay(50);
    analogWrite(redLedPin,0);
    delay(50);
  }
    for(int i = 30; i < 225; i+=13)
  {
    analogWrite(greenLedPin,i);
    delay(50);
    analogWrite(greenLedPin,0);
    delay(50);
  }
    for(int i = 30; i < 225; i+=12)
  {
    analogWrite(blueLedPin,i);
    delay(50);
    analogWrite(blueLedPin,0);
    delay(50);
  }

  offAll();
  delay(1000);
  analogWrite(greenLedPin,225);
  analogWrite(redLedPin,225);
  delay(750);
  analogWrite(greenLedPin,0);
  analogWrite(blueLedPin,225);
  analogWrite(redLedPin,225);
    delay(750);
  analogWrite(greenLedPin,225);
  analogWrite(blueLedPin,225);
  analogWrite(redLedPin,0);
      delay(750);
  analogWrite(greenLedPin,225);
  analogWrite(blueLedPin,0);
  analogWrite(redLedPin,225);
        delay(750);
  analogWrite(greenLedPin,86);
  analogWrite(blueLedPin,215);
  analogWrite(redLedPin,70);

  delay(1000);
  Serial.write(0);
}
