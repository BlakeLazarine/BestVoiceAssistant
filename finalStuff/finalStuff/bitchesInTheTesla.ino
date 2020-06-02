void bitchesInTheTesla()
{
  lcd.setCursor(0,0);
  lcd.print("Hey Alexa");
  delay(1400);
  lcd.setCursor(0,1);
  lcd.print("Hey Alexa");
  delay(1400);

  lcd.setCursor(0,0);
  lcd.print("                 ");
  lcd.setCursor(0,1);
  lcd.print("                 ");

  lcd.setCursor(0,0);
  lcd.print("How");
  delay(350);
  lcd.setCursor(4,0);
  lcd.print("many");
  delay(350);
  lcd.setCursor(9,0);
  lcd.print("bitches");
  delay(350);

  lcd.setCursor(0,1);
  lcd.print("can");
  delay(200); 
  lcd.setCursor(4,1);
  lcd.print("we");
  delay(250);
  lcd.setCursor(7,1);
  lcd.print("fit");
  delay(300);
  lcd.setCursor(11,1);
  lcd.print("in");
  delay(350);

  lcd.setCursor(0,0); lcd.print("                   ");
  lcd.setCursor(0,1); lcd.print("                   ");

  lcd.setCursor(0,0);
  lcd.print("the");
  delay(200);
  lcd.setCursor(4,0);
  lcd.print("Tesla?");
  delay(1000);
  lcd.clear();
  Serial.write(0);
}
