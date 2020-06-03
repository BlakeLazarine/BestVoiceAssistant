//Generic Version

void getText()
{
  String text = Serial.readString();

  int howMuch = 16;
  while(howMuch < text.length())
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(text.substring(howMuch - 16, howMuch));
    howMuch = howMuch + 16;
    delay(1000);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(text.substring(howMuch - 16, howMuch));
  delay(1000);

  lcd.clear();

  Serial.write("textDone");
}

