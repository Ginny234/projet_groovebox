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

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


bool lit_sequence;
int sequence_lue;
unsigned long debut_attente;
unsigned long fin_attente;

void setup() {
  lit_sequence=false;
  sequence_lue=-1;

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

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  AudioMemory(10);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.8);
  mixer1.gain(2, 0.8);
  mixer1.gain(3, 0.8);

  mixer2.gain(0, 0.8);
  mixer2.gain(1, 0.8);
  mixer2.gain(2, 0.8);
  mixer2.gain(3, 0.8);

  mixer3.gain(0, 0.8);
  mixer3.gain(1, 0.8);
  mixer3.gain(2, 0.8);
  mixer3.gain(3, 0.8);

  Serial.println("Audio ready");

  for(int i=0; i!=7; i++){
    pinMode(i, INPUT_PULLUP);
  }
  //jsp pk mais ca veut pas pr la 7
  //pareil la 8 ça fait des truc spéciaux aussi jsp si c'est le programme, la teensy ou la breadboard...
  pinMode(9, INPUT_PULLUP);
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
  display.clearDisplay();

  //affichage_normal();
  // Controle du volume en etat NORMAL
  if (fonctionnement==NORMAL){
    affichage_normal();
  }
  
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
    //printf("%d\n", position_menu);
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
      sequence_lue=-1;
    }
  }

  fonctionnement_sample();
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

