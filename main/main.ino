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

  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.8);
  mixer1.gain(2, 0.8);
  mixer1.gain(3, 0.8);
  printf("a\n");
  setupMicrophone();

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

  mixer8.gain(0, 0);
  mixer8.gain(1, 0.8);
  mixer8.gain(2, 0.8);
  mixer8.gain(3, 0.8);

  reverb1.reverbTime(0.5);
  Serial.println("Audio ready");

  for(int i=0; i!=7; i++){
    pinMode(i, INPUT_PULLUP);
  }
  //jsp pk mais ca veut pas pr la 7
  //pareil la 8 ça fait des truc spéciaux aussi jsp si c'est le programme, la teensy ou la breadboard...
  pinMode(9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
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
  bouton_effets.update();
  display.clearDisplay();
  updateMicrophone();
  
  static long somme = 0;
  static int nb_lectures = 0;

  somme += analogRead(A1);
  nb_lectures++;

  if (nb_lectures >= 64) {  // 64 au lieu de 16
    int val1 = somme / 64;
    somme = 0;
    nb_lectures = 0;

    int val_min = 0;
    int val_max = 1023;
    volume_courant = constrain(map(val1, val_min, val_max, 0, 1000), 0, 1000) / 1000.0;

    sgtl5000_1.volume(volume_courant);
    Serial.print("brut A1 = ");
    Serial.print(val1);
    Serial.print("  ->  volume = ");
    Serial.println(volume_courant);
  }

  //affichage_normal();
  fonctionnement_sample();
  
  if (fonctionnement==MENU){
    long newPosition = myEnc.read();
    if (newPosition != oldPosition) {
      //Serial.println(newPosition);
      printf("avant:%d, après:%d\n", newPosition, oldPosition);
      if(newPosition<oldPosition){
        position_menu=monter_position(position_menu, NBR_SEQUENCES-1);
        //printf("haut\n");
      }
      else{
        position_menu=baisser_position(position_menu);
        //printf("bas\n");
      }
      oldPosition = newPosition;
    }
    affichage_menu(position_menu);
  }
  if(fonctionnement==ENREGISTREMENT_SEQUENCE){
    affichage_enregistrement();
    /*if (button0.fallingEdge()) {
      tab_seq[position_menu]=ajouter_sequence(initia_sequence(0), tab_seq[position_menu]);
      printf("son bouton 1 seq\n");
    }*/
    for(int i=0; i!=NBR_BOUTONS_SON; i++){
      if(tab_boutons_son[i].fallingEdge()){
        tab_seq[position_menu]=ajouter_sequence(initia_sequence(i), tab_seq[position_menu]);
      }
    }
  }

  if (bouton_sequence.fallingEdge()){
    if(fonctionnement==NORMAL){
      fonctionnement=MENU;
      printf("bonjour je suis censé afficher un menu\n");
    }
    else if(fonctionnement==MENU){
      fonctionnement=NORMAL;
      printf("bonjour je retourne au vide\n");
    }
  }
  if(bouton_ok.fallingEdge()){
    printf("ok...\n");
    if(fonctionnement==MENU){
      debut_attente=millis();
      while(digitalRead(SW)==LOW){
        fin_attente=millis();
      }
      if(fin_attente-debut_attente>3000 || tab_seq[position_menu]==NULL){
        tab_seq[position_menu]=NULL;
        fonctionnement=ENREGISTREMENT_SEQUENCE;
        printf("fonct:%d\n",fonctionnement);
        printf("enregistrement de sequence\n");
      }
      else if (tab_seq[position_menu]!=NULL){
        printf("je suis censer lire  une sequence\n");
        lire_sequence(tab_seq[position_menu]);
      }
      printf("debut:%d, fin:%d\n",debut_attente, fin_attente);
    }
    else if(fonctionnement==ENREGISTREMENT_SEQUENCE){
      printf("enregistrement terminé\n");
      fonctionnement=NORMAL;
    }
    if(fonctionnement==LECTURE_SEQUENCE){
      fonctionnement=NORMAL;
    }
  }
  if(bouton_effets.fallingEdge()){
    printf("bonjour\n");
    effet_actif=monter_position(effet_actif, 2);
    switch(effet_actif){
      case AUCUN:
        mixer8.gain(0, 0);
        mixer8.gain(1, 0.8);
        mixer8.gain(2, 0);
        mixer8.gain(3, 0);
        break;
      case REVERB:
        mixer8.gain(0, 1.6);
        mixer8.gain(1, 0);
        mixer8.gain(2, 0);
        mixer8.gain(3, 0);
        break;
      case ROBOTIQUE:
        mixer8.gain(0, 0);
        mixer8.gain(1, 0);
        mixer8.gain(2, 1.6);
        mixer8.gain(3, 0);
        break;
      default:
        effet_actif=AUCUN;
        break;
    }
    printf("je dois encleché un effet, %d\n");
  }

  fonctionnement_sample();
  affichage_normal();//affichage des samples quand elles sont jouées
  affichage_base();
  display.display();

  /*int knob = analogRead(A3);
  if (button0.fallingEdge()) {
    if (knob < 512) {
      playMem1.play(AudioSampleSnare);
    } else {
      playMem1.play(AudioSampleKick);
    }
  }
  if (button1.fallingEdge()) {
    if (knob < 512) {
      playMem2.play(AudioSampleTomtom);
    } else {
      playMem4.play(AudioSampleGong);
    }
  }
  if (button2.fallingEdge()) {
    if (knob < 512) {
      playMem3.play(AudioSampleHihat);
    } else {
      playMem3.play(AudioSampleCashregister);
    }
  }*/

}

