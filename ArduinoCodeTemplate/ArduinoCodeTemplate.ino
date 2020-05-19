const int PWMPin = 9;
int buffer [1024];
int bri = 225;
int red = 2;
int blue = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMPin, OUTPUT);
  Serial.begin(115200);
  ADCSRA = (ADCSRA & 0xf8) | 0x04;
}

void recordSample() {
  // put your main code here, to run repeatedly:
  analogWrite(PWMPin, bri);
  for (int i = 0; i < 1024; i++) {
    buffer[i] = analogRead(A0);
  }
  for (int i = 0; i < 1024; i++) {
    Serial.write(buffer[i]);
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
  switch (in) {
    case 1:
      recordSample();
      break;
    case 2:
      lightRed();
      break;
    case 3:
      lightBlue();
      break;
    case 4:
      writeThing();
      break;
    default:
      break;
  }
}
