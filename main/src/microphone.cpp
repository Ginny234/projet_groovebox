#include "microphone.h"
#include "var_global.h"

File frec;

const int chipSelect = BUILTIN_SDCARD;
const int buttonPin = 12;

unsigned long startTime;
bool recording = false;
bool playing = false;
bool fileReady = false;

bool buttonPressed = false;
unsigned long buttonPressTime = 0;
bool longPressDone = false;

void handleButton();
void startRecording();
void continueRecording();
void stopRecording();
void playRecording();

void microphoneSetup() {
  pinMode(buttonPin, INPUT_PULLUP);

  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(30);

  Serial.println("Micro OK");
  Serial.println("Appui long 3s = enregistrer 5s");
  Serial.println("Appui court = lire");
}

void microphoneLoop() {
  handleButton();

  if (recording) {
    continueRecording();

    if (millis() - startTime >= 5000) {
      stopRecording();
    }
  }

  if (playing && !playRaw1.isPlaying()) {
    Serial.println("Lecture terminee");
    playing = false;
  }
}

void handleButton() {
  bool pressed = digitalRead(buttonPin) == LOW;

  if (pressed && !buttonPressed) {
    delay(30);
    if (digitalRead(buttonPin) == LOW) {
      buttonPressed = true;
      buttonPressTime = millis();
      longPressDone = false;
    }
  }

  if (pressed && buttonPressed && !longPressDone) {
    if (millis() - buttonPressTime >= 3000) {
      startRecording();
      longPressDone = true;
    }
  }

  if (!pressed && buttonPressed) {
    delay(30);
    if (digitalRead(buttonPin) == HIGH) {
      buttonPressed = false;

      if (!longPressDone) {
        playRecording();
      }
    }
  }
}

void startRecording() {
  if (recording) return;

  if (playing) {
    playRaw1.stop();
    playing = false;
    delay(200);
  }

  if (SD.exists("RECORD.RAW")) {
    SD.remove("RECORD.RAW");
  }

  frec = SD.open("RECORD.RAW", FILE_WRITE);

  if (!frec) {
    Serial.println("Erreur ouverture fichier");
    return;
  }

  Serial.println("Enregistrement pendant 5 secondes...");
  queue1.begin();
  recording = true;
  fileReady = false;
  startTime = millis();
}

void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];

    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();

    memcpy(buffer + 256, queue1.readBuffer(), 256);
    queue1.freeBuffer();

    frec.write(buffer, 512);
  }
}

void stopRecording() {
  Serial.println("Arret enregistrement");

  queue1.end();

  while (queue1.available() > 0) {
    frec.write((byte*)queue1.readBuffer(), 256);
    queue1.freeBuffer();
  }

  frec.close();
  recording = false;
  fileReady = true;

  Serial.println("Fichier sauvegarde");
}

void playRecording() {
  if (recording) return;

  if (!fileReady && !SD.exists("RECORD.RAW")) {
    Serial.println("Aucun fichier a lire");
    return;
  }

  if (playing) {
    playRaw1.stop();
    playing = false;
    delay(200);
  }

  Serial.println("Lecture du fichier...");
  playRaw1.play("RECORD.RAW");
  playing = true;
}