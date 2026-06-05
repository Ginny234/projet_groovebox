// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-3: Playing Samples

// WAV files converted to code by wav2sketch
#include "AudioSampleSnare.h"        // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"       // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"        // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleKick.h"         // http://www.freesound.org/people/DWSD/sounds/171104/
#include "AudioSampleGong.h"         // http://www.freesound.org/people/juskiddink/sounds/86773/
#include "AudioSampleCashregister.h" // http://www.freesound.org/people/kiddpark/sounds/201159/
#include <Bounce.h>


///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem3;  //xy=220.33332061767578,352.333309173584
AudioPlayMemory          playMem2;       //xy=244.3333282470703,293.3333282470703
AudioPlayMemory          playMem4; //xy=246.33330535888672,411.3333387374878
AudioPlayMemory          playMem1;       //xy=257.3333282470703,207.3333282470703
AudioMixer4              mixer1;         //xy=471.3333282470703,217.3333282470703
AudioOutputI2S           i2s1;           //xy=671.3333282470703,240.3333282470703
AudioConnection          patchCord1(playMem3, 0, mixer1, 2);
AudioConnection          patchCord2(playMem2, 0, mixer1, 1);
AudioConnection          patchCord3(playMem4, 0, mixer1, 3);
AudioConnection          patchCord4(playMem1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=395.3333282470703,341.3333282470703
// GUItool: end automatically generated code

///////////////////////////////////
#define NBR_SEQUENCES 4
#define NBR_BOUTONS 7

typedef enum {
  MENU,
  NORMAL,
  ENREGISTREMENT_SEQUENCE,
}etat;
typedef struct sequence sequence;
struct sequence{
  int id_sample;
  sequence* suiv;
};

sequence* initia_sequence(int id_sample){
  sequence* nv_seq=malloc(sizeof(sequence));
  nv_seq->id_sample=id_sample;
  nv_seq->suiv=NULL;
  return nv_seq;
}

sequence* ajouter_sequence(sequence* nv_sample, sequence* seq){
  if(seq!=NULL){
    sequence* temp=seq;
    while(temp->suiv!=NULL){
      temp=temp->suiv;
    }
    temp->suiv=nv_sample;
  }
  else{
    seq=nv_sample;
  }
  return seq;
}

void lire_sample(int id){
  switch(id){
    case 0:
      playMem1.play(AudioSampleSnare);
    case 1:
      playMem2.play(AudioSampleTomtom);
    case 2:
      playMem3.play(AudioSampleHihat);
  }
}

void lire_sequence(sequence* seq){
  sequence* temp=seq;
  while(temp!=NULL){
    temp=temp->suiv;
    printf("%d\n", temp->id_sample);
    //lire_sample(temp->id_sample);
  }
}

void affichage_menu(int position_actuelle){
  //à changer quand on aura un écran (si on en a un...)
  printf("selectionné: %d\n", position_actuelle);
}



// Bounce objects to read pushbuttons 
Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);  // 15 ms debounce time
Bounce button2 = Bounce(2, 15);
Bounce bouton_sequence = Bounce(3, 15);
Bounce bouton_haut = Bounce(4, 15);
Bounce bouton_bas = Bounce(5, 15);
Bounce bouton_ok = Bounce(6, 15);

//autres variables
etat fonctionnement;
int position_menu=0;
sequence* tab_seq[NBR_SEQUENCES];


void setup() {
  for (int i=0; i!=NBR_BOUTONS; i++){
    pinMode(i, INPUT_PULLUP);
  }
  for(int i=0; i!=NBR_SEQUENCES; i++){
    tab_seq[i]=NULL;
  }
  fonctionnement=NORMAL;
  /*pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);*/
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.8);
  mixer1.gain(2, 0.8);
  mixer1.gain(3, 0.8);
  printf("a\n");
}

void fonctionnement_sample(){
  button0.update();
  button1.update();
  button2.update();

  if (button0.fallingEdge()) {
    printf("son bouton 1\n");
    playMem1.play(AudioSampleSnare);
  }
  if (button1.fallingEdge()) {
    printf("son bouton 2\n");
    playMem2.play(AudioSampleTomtom);
  }
  if (button2.fallingEdge()) {
    printf("son bouton 3\n");
    playMem3.play(AudioSampleHihat);
  }
}

int baisser_position(int position){
  if (position--<=0){
    return 0;
  }
  return position--;
}

int monter_position(int position, int max){
  if (position++>=max){
    return max;
  }
  return position++;
}

void loop() {
  // Update all the button objects
  bouton_haut.update();
  bouton_bas.update();
  bouton_ok.update();
  bouton_sequence.update();
  /*if (bouton_ok.fallingEdge()){
      printf("ok\n");
  }*/
  if (bouton_haut.fallingEdge()){
      printf("bas\n");
    }
  if (bouton_bas.fallingEdge()){
      printf("haut\n");
    }
  if (fonctionnement==MENU){
    //printf("aafg\n");
    if (bouton_haut.fallingEdge()){
      
      position_menu=baisser_position(position_menu);
      affichage_menu(position_menu);
    }
    if (bouton_bas.fallingEdge()){
      position_menu=monter_position(position_menu, NBR_SEQUENCES);
      affichage_menu(position_menu);
    }
    if (bouton_sequence.fallingEdge()){
      //fonctionnement=NORMAL;
    }
    //rising edge p
    if (bouton_ok.risingEdge()){
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

  if (bouton_sequence.fallingEdge() && fonctionnement==NORMAL){
    printf("bonjour je suis censé afficher un menu\n");
    fonctionnement=MENU;
    printf("fonct:%d\n",fonctionnement);
  }
/*
  int knob = analogRead(A3);
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
  }
*/

}

