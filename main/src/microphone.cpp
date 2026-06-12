#include "microphone.h"

// Audio objects
AudioInputI2S      i2s_in;
AudioRecordQueue   queue1;
AudioPlaySdRaw     playRaw1;
AudioOutputI2S     i2s_out;

AudioConnection patchCord1(i2s_in, 0, queue1, 0);
AudioConnection patchCord2(playRaw1, 0, i2s_out, 0);
AudioConnection patchCord3(playRaw1, 0, i2s_out, 1);

AudioControlSGTL5000 sgtl5000_1;

// Button
Bounce boutonRec = Bounce(PIN_BOUTON_REC, 15);

// State variables
bool recording = false;
bool boutonEnfonce = false;
bool appuiLongDejaDeclenche = false;

// File handle
File frec;

// Timestamps
unsigned long startTime = 0;
unsigned long appuiDebut = 0;

void setupMicrophone() {
  pinMode(PIN_BOUTON_REC, INPUT_PULLUP);

  AudioMemory(60);

  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(45);
  sgtl5000_1.volume(0.9);

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Erreur SD");
    while (1);
  }

  Serial.println("SD OK");
  Serial.println("Maintiens le bouton 3 secondes pour enregistrer.");
}

void demarrerEnregistrement() {
  if (recording) return;

  if (playRaw1.isPlaying()) {
    playRaw1.stop();
  }

  SD.remove("REC.RAW");
  frec = SD.open("REC.RAW", FILE_WRITE);

  if (!frec) {
    Serial.println("Erreur creation fichier");
    return;
  }

  Serial.println("Nouvel enregistrement 5 secondes...");
  queue1.begin();
  recording = true;
  startTime = millis();
}

void arreterEnregistrementEtLire() {
  queue1.end();

  while (queue1.available() > 0) {
    queue1.freeBuffer();
  }

  frec.close();
  recording = false;

  Serial.println("Enregistrement termine");

  File f = SD.open("REC.RAW");
  Serial.print("Taille fichier = ");
  Serial.println(f.size());
  f.close();

  delay(1000);

  Serial.println("Lecture...");
  playRaw1.play("REC.RAW");
}

void updateMicrophone() {
  boutonRec.update();

  if (boutonRec.fallingEdge()) {
    appuiDebut = millis();
    boutonEnfonce = true;
    appuiLongDejaDeclenche = false;
    Serial.println("Bouton appuye...");
  }

  if (boutonRec.risingEdge()) {
    boutonEnfonce = false;
    appuiLongDejaDeclenche = false;
    Serial.println("Bouton relache");
  }

  if (boutonEnfonce && !appuiLongDejaDeclenche && millis() - appuiDebut >= 3000) {
    appuiLongDejaDeclenche = true;
    demarrerEnregistrement();
  }

  if (recording && millis() - startTime > 5000) {
    arreterEnregistrementEtLire();
  }

  if (recording && queue1.available() > 0) {
    byte *buffer = (byte *)queue1.readBuffer();
    frec.write(buffer, 256);
    queue1.freeBuffer();
  }
}
