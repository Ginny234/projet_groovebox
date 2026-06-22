// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-3: Playing Samples

// WAV files converted to code by wav2sketch

#include <Encoder.h>

#include "src/struct.h"
#include "src/var_global.h"
#include "src/affichage.h"
#include "src/menus.h"
#include "src/modifs_son.h"
#include "src/samples.h"
#include "src/sequences.h"
#include "src/microphone.h"

bool lit_sequence;
int sequence_lue;

Encoder myEnc(DT, CLK);
long oldPosition = -999;

void setup() {
  lit_sequence = false;
  sequence_lue = -1;
  volume_courant = 1.0f;

  for (int i = 0; i != NBR_SEQUENCES; i++) {
    tab_seq[i] = NULL;
  }

  Serial.begin(9600);

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  AudioMemory(80);

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Erreur SD");
    while (1);
  }

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.8);
  mixer1.gain(2, 0.8);
  mixer1.gain(3, 0.8);

  microphoneSetup();

  mixer2.gain(0, 0.8);
  mixer2.gain(1, 0.8);
  mixer2.gain(2, 0.8);
  mixer2.gain(3, 0.8);

  mixer3.gain(0, 0.8);
  mixer3.gain(1, 0.8);
  mixer3.gain(2, 0.8);
  mixer3.gain(3, 0.8);

  mixer4.gain(0, 0.8);
  mixer4.gain(1, 0.8);
  mixer4.gain(2, 0.8);
  mixer4.gain(3, 0.8);

  mixer5.gain(0, 0.8);
  mixer5.gain(1, 0.8);
  mixer5.gain(2, 0.8);
  mixer5.gain(3, 0.8);

  mixer6.gain(0, 0.8);
  mixer6.gain(1, 0.8);
  mixer6.gain(2, 0.8);
  mixer6.gain(3, 0.8);

  mixer7.gain(0, 0.8);
  mixer7.gain(1, 0.8);
  mixer7.gain(2, 0.8);
  mixer7.gain(3, 0.8);

  mixerFinal.gain(0, 0.8);  // samples
  mixerFinal.gain(1, 0.8);  // lecture micro
  mixerFinal.gain(2, 0.0);
  mixerFinal.gain(3, 0.0);

  Serial.println("Audio ready");

  for (int i = 0; i != 7; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(9, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  bouton_ok.update();
  bouton_sequence.update();

  display.clearDisplay();

  microphoneLoop();

  fonctionnement_sample();

  if (fonctionnement == MENU) {
    affichage_menu(position_menu);
  }

  if (fonctionnement == ENREGISTREMENT_SEQUENCE) {
    affichage_enregistrement();

    for (int i = 0; i != NBR_BOUTONS_SON; i++) {
      if (tab_boutons_son[i].fallingEdge()) {
        tab_seq[position_menu] = ajouter_sequence(initia_sequence(i), tab_seq[position_menu]);
      }
    }
  }

  if (bouton_sequence.fallingEdge()) {
    if (fonctionnement == NORMAL) {
      fonctionnement = MENU;
      printf("bonjour je suis censé afficher un menu\n");
    } 
    else if (fonctionnement == MENU) {
      fonctionnement = NORMAL;
      printf("bonjour je retourne au vide\n");
    }
  }

  if (bouton_ok.fallingEdge()) {
    printf("ok...\n");

    if (fonctionnement == MENU) {
      debut_attente = millis();

      while (digitalRead(SW) == LOW) {
        fin_attente = millis();
      }

      if (fin_attente - debut_attente > 3000 || tab_seq[position_menu] == NULL) {
        tab_seq[position_menu] = NULL;
        fonctionnement = ENREGISTREMENT_SEQUENCE;
        printf("fonct:%d\n", fonctionnement);
        printf("enregistrement de sequence\n");
      } 
      else if (tab_seq[position_menu] != NULL) {
        printf("je suis censer lire une sequence\n");
        lire_sequence(tab_seq[position_menu]);
      }

      printf("debut:%lu, fin:%lu\n", debut_attente, fin_attente);
    } 
    else if (fonctionnement == ENREGISTREMENT_SEQUENCE) {
      printf("enregistrement terminé\n");
      fonctionnement = NORMAL;
    }

    if (fonctionnement == LECTURE_SEQUENCE) {
      fonctionnement = NORMAL;
      sequence_lue = -1;
    }
  }

  affichage_normal();
  affichage_base();
  display.display();
}