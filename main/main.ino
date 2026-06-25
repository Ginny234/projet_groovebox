// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-3: Playing Samples

// WAV files converted to code by wav2sketch
#include <math.h>
#include "src/struct.h"
#include "src/var_global.h"
#include "src/affichage.h"
#include "src/menus.h"
#include "src/modifs_son.h"
#include "src/samples.h"
#include "src/sequences.h"

void setup() {
  Serial.begin(9600);
  for (int i=0; i!=NBR_BOUTONS; i++){
    pinMode(i, INPUT_PULLUP);
  }
  //for(int i=0; i!=NBR_SEQUENCES; i++){
  //  tab_seq[i]=NULL;
  //}

  // Initialisation I2C sur Teensy (pins 18/19 par défaut)
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  analogReadResolution(10);
  analogReadAveraging(16);

  fonctionnement=NORMAL;
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(volume_courant);
  mixer1.gain(0, 0.18);
  mixer1.gain(1, 0.18);
  mixer1.gain(2, 0.18);
  mixer1.gain(3, 0.18);
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  granular1.beginPitchShift(12.0f);
  Serial.println("Pitch monitoring started");
}

void loop() {
  // Update all the button objects
  bouton_haut.update();
  bouton_bas.update();
  bouton_ok.update();
  bouton_sequence.update();
  display.clearDisplay();
  aigue_grave();
  //affichage_normal();
  fonctionnement_sample();
  // Controle du volume en etat NORMAL
  if (fonctionnement==NORMAL){
    if(playMem1.isPlaying() || playMem2.isPlaying() || playMem3.isPlaying()){
      affichage_sample(0);
      //display.setCursor(0, 0);
      //display.print("Sample jouée");
      //display.display();
      //delay(300);
    }
    affichage_normal();
    if (bouton_haut.fallingEdge()){
      augmenter_volume();
      printf("je dois augmenter le volume");
    }
    if (bouton_bas.fallingEdge()){
      baisser_volume();
      printf("je dois baisser le volume");
    }
  }
  
  if (fonctionnement==MENU){
    affichage_menu(position_menu);
    if (bouton_haut.fallingEdge()){
      printf("haut\n");
      position_menu=baisser_position(position_menu);
      affichage_menu(position_menu);
    }
    if (bouton_bas.fallingEdge()){
      position_menu=monter_position(position_menu, NBR_SEQUENCES-1);
      affichage_menu(position_menu);
      printf("bas\n");
    }
    //rising edge parce que si c'est pas l'inverse ça considérait qu'on appuyait sur le bouton 2 fois
    if (bouton_ok.fallingEdge()){
      if(tab_seq[position_menu]!=NULL){
        printf("je suis censer lire  une sequence\n");
        lire_sequence(tab_seq[position_menu]);
      }
      else{
        fonctionnement=ENREGISTREMENT_SEQUENCE;
        printf("fonct:%d\n",fonctionnement);
        printf("enregistrement de sequence\n");
      }
    }
    //affichage_menu_sequences(position_menu);
  }
  if(fonctionnement==ENREGISTREMENT_SEQUENCE){
    if (button0.fallingEdge()) {
      tab_seq[position_menu]=ajouter_sequence(initia_sequence(0), tab_seq[position_menu]);
      printf("son bouton 1 seq\n");
    }
    if (button1.fallingEdge()) {
      tab_seq[position_menu]=ajouter_sequence(initia_sequence(1), tab_seq[position_menu]);
      printf("son bouton 2 seq\n");
    }
    if (button2.fallingEdge()) {
      tab_seq[position_menu]=ajouter_sequence(initia_sequence(2), tab_seq[position_menu]);
      printf("son bouton 3 seq\n");
    }
    if (bouton_ok.fallingEdge()){
      printf("enregistrement terminé\n");
      fonctionnement=NORMAL;
    }
  }

  fonctionnement_sample();

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

  /*display.setCursor(SCREEN_WIDTH/2-strlen("GROUPE VOCODEUR")*11/4, SCREEN_HEIGHT-8);
  display.print("GROUPE VOCODEUR\n");*/
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

