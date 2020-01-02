int speakerPin = 9;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playMyNote(String note, int duration) {
  String names[] = { "c", "d", "d#", "e", "f", "g", "g#", "a", "a#", "e2", "b3", "g3", "c3", "e3" };
  int tones[] = { 1915, 1700, 1608, 1519, 1432, 1275, 1205, 1136, 1073, NOTE_E2, NOTE_B3, NOTE_G3, NOTE_C3, NOTE_E3 };

  for (int i = 0; i < 14; i++) {
    if (names[i] == note) {
      Serial.println("found: " + String(i));
      // playTone(tones[i], duration);
      tone(speakerPin, tones[i], duration);
    }
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

void playSong(String notes, int beats[], int tempo, int length) {
  for (int i = 0; i < length; i+=2) {
    String thisNote = String(notes[i]) + String(notes[i+1]);
    Serial.println("play: " + thisNote);
    if (thisNote == "  ") {
      delay(beats[i] * tempo); // rest
    } else {
      playMyNote(thisNote, beats[i] * tempo);
    }

//     // pause between notes
    delay(tempo / 2);
  }
}

void playThisSong() {
  int length = 6; // the number of notes
  String notes = "c3e3c3"; // a space represents a rest
  int beats[] = { 1, 1, 1, 1, 2, 2};
  int tempo = 600;
  playSong(notes, beats, tempo, length);
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