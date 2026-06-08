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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


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
    return nv_sample;
  }
  return seq;
}

void lire_sample(int id){
  switch(id){
    case 0:
      playMem1.play(AudioSampleSnare);
      break;
    case 1:
      playMem2.play(AudioSampleTomtom);
      break;
    case 2:
      playMem3.play(AudioSampleHihat);
      break;
  }
}

void lire_sequence(sequence* seq){
  sequence* temp=seq;
  while(temp!=NULL){
    printf("%d\n", temp->id_sample);
    lire_sample(temp->id_sample);
    delay(400);
    temp=temp->suiv;
  }
}

void affichage_menu(int position_actuelle){
  display.clearDisplay();
  display.setCursor(0, 0);
  //display.print("test\n");
  //display.display();
  for(int i=0; i!=NBR_SEQUENCES; i++){
    if(i==position_actuelle){
      display.print("->");
    }
    display.print("Sequence\n");
  }
  display.display();
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
float volume_courant=0.5f;  // Volume initial entre 0 et 1
const float VOLUME_MIN=0.0f;
const float VOLUME_MAX=1.0f;
const float VOLUME_STEP=0.05f;


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

  fonctionnement=NORMAL;
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(volume_courant);
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

void augmenter_volume(){
  if (volume_courant < VOLUME_MAX){
    volume_courant += VOLUME_STEP;
    if (volume_courant > VOLUME_MAX){
      volume_courant = VOLUME_MAX;
    }
    sgtl5000_1.volume(volume_courant);
    printf("Volume augmente: %.2f\n", volume_courant);
  }
}

void baisser_volume(){
  if (volume_courant > VOLUME_MIN){
    volume_courant -= VOLUME_STEP;
    if (volume_courant < VOLUME_MIN){
      volume_courant = VOLUME_MIN;
    }
    sgtl5000_1.volume(volume_courant);
    printf("Volume baisse: %.2f\n", volume_courant);
  }
}

void loop() {
  // Update all the button objects
  bouton_haut.update();
  bouton_bas.update();
  bouton_ok.update();
  bouton_sequence.update();

  /*display.clearDisplay();
  display.setCursor(0, 0);
  display.print("test\n");
  display.display();*/

  fonctionnement_sample();
  // Controle du volume en etat NORMAL
  if (fonctionnement==NORMAL){
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
    if (bouton_sequence.fallingEdge()){
      //fonctionnement=NORMAL;
    }
    //rising edge parce que si c'est pas l'inverse ça considérait qu'on appuyait sur le bouton 2 fois
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

  if (bouton_sequence.fallingEdge() /*&& fonctionnement==NORMAL*/){
    printf("bonjour je suis censé afficher un menu\n");
    fonctionnement=MENU;
    printf("fonct:%d\n",fonctionnement);
  }

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


}

