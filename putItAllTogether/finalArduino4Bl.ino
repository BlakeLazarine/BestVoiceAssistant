#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int LCDPin = 7;
const int BUZZERPin = 8;
const int PWMPin = 9;
int buffer [512];
int bri = 225;
const int red = 11;
const int blue = 12;
const int green = 13;



int note_vals[] = {31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978};

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

void offAll()
{
  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
}

void lightShow()
{
  offAll();
  delay(1000);

  analogWrite(red,75);
  delay(300);
  analogWrite(blue,125);
  delay(300);
  analogWrite(green,175);
  delay(300);

  offAll();

  for(int i = 30; i < 225; i+=12)
  {
    analogWrite(red,i);
    delay(50);
    analogWrite(red,0);
    delay(50);
  }
    for(int i = 30; i < 225; i+=13)
  {
    analogWrite(green,i);
    delay(50);
    analogWrite(green,0);
    delay(50);
  }
    for(int i = 30; i < 225; i+=12)
  {
    analogWrite(blue,i);
    delay(50);
    analogWrite(blue,0);
    delay(50);
  }

  offAll();
  delay(1000);
  analogWrite(green,225);
  analogWrite(red,225);
  delay(750);
  analogWrite(green,0);
  analogWrite(blue,225);
  analogWrite(red,225);
    delay(750);
  analogWrite(green,225);
  analogWrite(blue,225);
  analogWrite(red,0);
      delay(750);
  analogWrite(green,225);
  analogWrite(blue,0);
  analogWrite(red,225);
        delay(750);
  analogWrite(green,86);
  analogWrite(blue,215);
  analogWrite(red,70);

  delay(1000);
  Serial.write(0);
}

void playSong()
{
  // change this to make the song slower or faster
  int tempo = 140;

  // change this to whichever pin you want to use
  int buzzer = 8;
  int notes = Serial.parseInt();
  while (notes == 0) {
    notes = Serial.parseInt();
  }
  while(!Serial.available()){}
  Serial.read();
  int melody[notes * 2];
  for (int i = 0; i < notes*2; i+=2)
  {
    //    delay(100);
    while(!Serial.available()){}
    byte val = Serial.read();
    
    if (val == 255)
      melody[i] = 0;
    else
      melody[i] = note_vals[val];
      
//    Serial.print(note_vals[val]);
//    Serial.print(" ");
    
    while(!Serial.available()){}
    val = Serial.read();
//    Serial.print(val);
//    Serial.print(" ");
    melody[i+1] = val;
    //    digitalWrite(7, LOW);
    //    delay(1000);

    //    Serial.print(7);
    //    Serial.println(val);
  }
  //  digitalWrite(7, HIGH);


  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  Serial.write(1);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Booting...");
  delay(3000);
  lcd.clear();
  
  Serial.begin(115200);
  pinMode(BUZZERPin, OUTPUT);
  pinMode(LCDPin, OUTPUT);
  digitalWrite(LCDPin, LOW);
  Serial.write(0);
  ADCSRA = (ADCSRA & 0xf8) | 0x04;
  delay(1000);
}

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

void sayAJoke()
{
  //tone(BUZZERPin,10,100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print("What ");
  tone(BUZZERPin,1000,100);
  delay(350);
  lcd.print("did ");
  tone(BUZZERPin,1000,100);
  delay(350);
  lcd.print("the ");
  tone(BUZZERPin,1000,100);
  delay(350);

  lcd.setCursor(0,1);
  lcd.print("pirate ");
  tone(BUZZERPin,1000,50);
  delay(100);
  tone(BUZZERPin,1000,50);
  delay(250);
  lcd.print("say ");
  tone(BUZZERPin,1000,100);
  delay(350);
  lcd.print("on ");
  tone(BUZZERPin,1000,100);

  lcd.setCursor(0,0);
  lcd.print("                             ");
  lcd.setCursor(0,0);
  lcd.print("his ");
  tone(BUZZERPin,1000,100);
  delay(350);
  lcd.print("80th ");
  tone(BUZZERPin,1000,100);
  delay(150);
  tone(BUZZERPin,1000,100);
  delay(150);
  tone(BUZZERPin,1000,100);
  delay(300);
  lcd.setCursor(0,1);
  lcd.print("                            ");
  lcd.setCursor(0,1);
  lcd.print("birthday?");
  tone(BUZZERPin,1000,100);
  delay(175);
  tone(BUZZERPin,1000,100);
  
  delay(2500);
  lcd.clear();
  delay(500);

  lcd.setCursor(0,0);
  lcd.print("AY M8E!");
  tone(BUZZERPin,1000,300);
  delay(3000);
}

void lightRed() {
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
}

void lightBlue() {
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
}

//For Testing
void writeThing() {
  Serial.write("hello\n");

}
void loop() {
  int in = Serial.parseInt();
  if(in / 10 == 1){
    recordSample(in%10);
    return;
    }
  switch (in) {
    case 1:
      //blue light
      lightBlue();
      break;
    case 2:
      //red light
      lightRed();
      break;
    case 3:
      //display time or weather
      getText();
      break;
    case 5:
      //joke
      sayAJoke();
      break;
    case 6:
      //song
      playSong();
      break;
    case 7:
      //light show
      lightShow();
      break;
    default:
      break;
  }
}
