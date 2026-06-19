// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-3: Playing Samples

// WAV files converted to code by wav2sketch

#include "src/struct.h"
#include "src/var_global.h"
#include "src/affichage.h"
#include "src/menus.h"
#include "src/modifs_son.h"
#include "src/samples.h"
#include "src/sequences.h"
#include "src/microphone.h"
//commentaire test

void setup() {
  volume_courant=1.0f;
  fonctionnement=NORMAL;

  for(int i=0; i!=NBR_SEQUENCES; i++){
    tab_seq[i]=NULL;
  }

  setupMicrophone();

  Serial.begin(9600);

  // Initialisation I2C sur Teensy (pins 18/19 par défaut)
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur OLED");
    while (1);
  }

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Erreur SD");
    while (1);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  AudioMemory(30);

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Erreur SD");
    while (1);
  }

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  // Voix propre type radio
  filter1.frequency(1000);
  filter1.resonance(1.5);

  // Robot léger
  modulator.begin(WAVEFORM_SINE);
  modulator.frequency(35); // essaie 25, 35, 50
  modulator.amplitude(0.5); // plus petit = plus propre

  reverb1.reverbTime(0.5);

  for(int i=0; i!=7; i++){
    pinMode(i, INPUT_PULLUP);
  }
  //jsp pk mais ca veut pas pr la 7
  //pareil la 8 ça fait des truc spéciaux aussi jsp si c'est le programme, la teensy ou la breadboard...
  pinMode(9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  setup_mixers();

  lire_fichier_sequence();
  printf("fin du setup");
}
#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(DT, CLK);
long oldPosition  = -999;
void loop() {
  bouton_ok.update();
  bouton_sequence.update();
  bouton_reset.update();

  display.clearDisplay();
  updateMicrophone();
  modifs_volume();
  //affichage_normal();
  fonctionnement_sample();
  
  if (fonctionnement==MENU){
    long newPosition = myEnc.read();
    if (newPosition != oldPosition) {
      if(newPosition<oldPosition){
        position_menu=monter_position(position_menu, NBR_SEQUENCES-1);
      }
      else{
        position_menu=baisser_position(position_menu);

      }
      oldPosition = newPosition;
    }
    affichage_menu(position_menu);
  }
  if(fonctionnement==ENREGISTREMENT_SEQUENCE){
    affichage_enregistrement();
    for(int i=0; i!=NBR_BOUTONS_SON; i++){
      if(tab_boutons_son[i].fallingEdge()){
        tab_seq[position_menu]=ajouter_sequence(initia_sequence(i), tab_seq[position_menu]);
      }
    }
  }

  if (bouton_sequence.fallingEdge()){
    if(fonctionnement==NORMAL){
      fonctionnement=MENU;
    }
    else if(fonctionnement==MENU){
      fonctionnement=NORMAL;
    }
  }
  if(bouton_ok.fallingEdge()){
    if(fonctionnement==MENU){
      debut_attente=millis();
      while(digitalRead(SW)==LOW){
        fin_attente=millis();
      }
      if(fin_attente-debut_attente>3000 || tab_seq[position_menu]==NULL){
        tab_seq[position_menu]=NULL;
        fonctionnement=ENREGISTREMENT_SEQUENCE;
      }
      else if (tab_seq[position_menu]!=NULL){
        lire_sequence(tab_seq[position_menu]);
      }
    }
    else if(fonctionnement==ENREGISTREMENT_SEQUENCE){
      sauvegarder_sequences(tab_seq);
      fonctionnement=NORMAL;
    }
    if(fonctionnement==LECTURE_SEQUENCE){
      fonctionnement=NORMAL;
    }
  }
  if(bouton_reset.fallingEdge()){
    reset();
  }

  fonctionnement_effets();
  fonctionnement_sample();
  affichage_normal();//affichage des samples quand elles sont jouées
  affichage_base();
  display.display();

}

