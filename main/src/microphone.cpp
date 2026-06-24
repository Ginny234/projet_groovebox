#include "microphone.h"
#include "var_global.h"

File frec;

const int chipSelect = BUILTIN_SDCARD;

unsigned long startTime;
bool recording = false;
bool playing = false;
bool fileReady = false;

bool buttonPressed = false;
unsigned long buttonPressTime = 0;
bool longPressDone = false;

void microphoneSetup() {
  pinMode(PIN_BOUTON_REC, INPUT_PULLUP);

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
  //bool pressed = digitalRead(PIN_BOUTON_REC) == LOW;
  boutonRec.update();

  if(boutonRec.fallingEdge()){
    printf("premier appui\n");
    debut_attente=millis();
    while(digitalRead(PIN_BOUTON_REC)==LOW){
      printf("t'apuies sur le bouton\n");
      fin_attente=millis();
    }
    printf("t'as arreter d'appuyé, temps attentte:%d\n", fin_attente-debut_attente);
    //si on était sur une séquence vide lors de l'appui ou qu'on a appuier pendant plus de 3 secondes onenregistrer une séquence à cet emplacement
    if(fin_attente-debut_attente>3000 || SD.exists("RECORD.RAW")==false){
      //printf("on lit un truc\n");
      startRecording();
    }
    //sinon on lit simplement la séquence
    else if (SD.exists("RECORD.RAW")){
      playRecording();
      //playRaw1.play("RECORD.RAW");
      //printf("yay\n");
    }
  }

  /*if (pressed && !buttonPressed) {
    //delay(30);
    if (digitalRead(PIN_BOUTON_REC) == LOW) {
      printf("c'est apuyé\n");
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
    if (digitalRead(PIN_BOUTON_REC) == HIGH) {
      buttonPressed = false;

      if (!longPressDone) {
        playRecording();
      }
    }
  }*/
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

  while (queue1.available()) {

    void *buffer = queue1.readBuffer();

    frec.write(buffer, 256);

    queue1.freeBuffer();
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