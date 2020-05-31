const int PWMPin = 9;
int buffer [512];
int bri = 225;
int red = 2;
int blue = 3;


void takeOnMe()
{
  // change this to make the song slower or faster
  int tempo = 140;

  // change this to whichever pin you want to use
  int buzzer = 8;
  int notes = Serial.parseInt();
  while (notes == 0) {
    notes = Serial.parseInt();
  }
  int melody[notes * 2];
  while(Serial.available())
    Serial.read();
  for (int i = 0; i < notes; i++)
  {
    //    delay(100);
    int val = Serial.parseInt();
    while (val == 0) {
      val = Serial.parseInt();
    }
    if (val == 255)
      val = 0;
    melody[i] = val;
    
    val = Serial.parseInt();
    while (val == 0) {
      val = Serial.parseInt();
    }
    melody[i] = val;
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
  Serial.begin(115200);
  Serial.write(0);
  ADCSRA = (ADCSRA & 0xf8) | 0x04;
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
      writeThing();
      break;
    case 2:
      lightRed();
      break;
    case 3:
      lightBlue();
      break;
    case 4:
      takeOnMe();
    default:
      break;
  }
}
