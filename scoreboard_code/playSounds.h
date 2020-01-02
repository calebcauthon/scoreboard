int speakerPin = 9;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playUpSound() {
  tone(speakerPin, NOTE_C4, 1000 / 4);
  delay(100);
  tone(speakerPin, NOTE_C5, 1000 / 4);
  delay(100);
  noTone(speakerPin);
}

void playDownSound() {
  tone(speakerPin, NOTE_C5, 1000 / 4);
  delay(100);
  tone(speakerPin, NOTE_C4, 1000 / 4);
  delay(100);
  noTone(speakerPin);
}

void playEndGameSound() {
  tone(speakerPin, NOTE_G3, 200);
  delay(200);

  tone(speakerPin, NOTE_C4, 300);
  delay(300);

  tone(speakerPin, NOTE_G3, 200);
  delay(200);

  tone(speakerPin, NOTE_C4, 300);
  delay(300);

  tone(speakerPin, NOTE_G3, 200);
  delay(200);

  tone(speakerPin, NOTE_C4, 300);
  delay(300);
}