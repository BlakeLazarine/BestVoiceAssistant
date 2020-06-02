const int PWMPin = 9;
int buffer [512];
int bri = 225;
int red = 2;
int blue = 3;

int note_vals[] = {31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978};

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
