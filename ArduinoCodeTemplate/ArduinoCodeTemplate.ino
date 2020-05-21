const int PWMPin = 9;
int buffer [512];
int bri = 225;
int red = 2;
int blue = 3;

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
    default:
      break;
  }
}
