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
  for (int i = 0; i < notes * 2; i++)
  {
    //    delay(100);
    int val = Serial.parseInt();
    while (val == 0) {
      val = Serial.parseInt();
    }
    if (val == 255)
      val = 0;
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
  Serial.begin(115200);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  Serial.write(2);
  while (!Serial.available()) {}
  delay(1000);
  takeOnMe();
}
void loop() {}
