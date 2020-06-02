void sayAJoke()
{
  //tone(buzzPin,10,100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print("What ");
  tone(buzzPin,1000,100);
  delay(350);
  lcd.print("did ");
  tone(buzzPin,1000,100);
  delay(350);
  lcd.print("the ");
  tone(buzzPin,1000,100);
  delay(350);

  lcd.setCursor(0,1);
  lcd.print("pirate ");
  tone(buzzPin,1000,50);
  delay(100);
  tone(buzzPin,1000,50);
  delay(250);
  lcd.print("say ");
  tone(buzzPin,1000,100);
  delay(350);
  lcd.print("on ");
  tone(buzzPin,1000,100);

  lcd.setCursor(0,0);
  lcd.print("                             ");
  lcd.setCursor(0,0);
  lcd.print("his ");
  tone(buzzPin,1000,100);
  delay(350);
  lcd.print("80th ");
  tone(buzzPin,1000,100);
  delay(150);
  tone(buzzPin,1000,100);
  delay(150);
  tone(buzzPin,1000,100);
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("                            ");
  lcd.setCursor(0,1);
  lcd.print("birthday?");
  tone(buzzPin,1000,100);
  delay(175);
  tone(buzzPin,1000,100);
  
  delay(2500);
  lcd.clear();
  delay(500);

  lcd.setCursor(0,0);
  lcd.print("AY M8E!");
  tone(buzzPin,1000,300);
  delay(3000);
}
