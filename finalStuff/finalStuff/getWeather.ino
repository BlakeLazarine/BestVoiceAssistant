//HARDCODED VERSION

void getWeather(){
  String temperature;
  String weatherState; //If we can read stuff like "sunny, Partly cloudy, or whatever"
  
  //Read in here
  
  
  lcd.setCursor(0,0);
  lcd.print("At UCLA, it is");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.setCursor(3,1);
  lcd.print((char)223);
  lcd.print("F and Cloudy"); //Or whatever state it is
  return;
}
