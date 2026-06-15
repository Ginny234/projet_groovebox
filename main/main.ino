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

bool lit_sequence;
int sequence_lue;
unsigned long debut_attente;
unsigned long fin_attente;

void setup() {
  lit_sequence=false;
  sequence_lue=-1;

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

void loop() {
  // Update all the button objects
  bouton_haut.update();
  bouton_bas.update();
  bouton_ok.update();
  bouton_sequence.update();
  display.clearDisplay();
  
  static long somme = 0;
  static int nb_lectures = 0;

  somme += analogRead(A0);
  nb_lectures++;

  if (nb_lectures >= 64) {  // 64 au lieu de 16
    int val1 = somme / 64;
    somme = 0;
    nb_lectures = 0;

    int val_min = 0;
    int val_max = 515;
    float volume = constrain(map(val1, val_min, val_max, 0, 1000), 0, 1000) / 1000.0;

    sgtl5000_1.volume(volume);
    Serial.print("brut A0 = ");
    Serial.print(val1);
    Serial.print("  ->  volume = ");
    Serial.println(volume);
  }

  //affichage_normal();
  fonctionnement_sample();
  
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
    //affichage_menu_sequences(position_menu);
  }
  if(fonctionnement==ENREGISTREMENT_SEQUENCE){
    affichage_enregistrement();
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
  }

  /*if(fonctionnement==LECTURE_SEQUENCE){
    if(tab_seq[sequence_lue]!=NULL){
      lire_sequence(tab_seq[sequence_lue]);
      fonctionnement=NORMAL;
    }
  }*/


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
    if(fonctionnement==MENU){
      debut_attente=millis();
      while(digitalRead(6)==LOW){
        fin_attente=millis();
      }
      if(fin_attente-debut_attente>3000 || tab_seq[position_menu]==NULL){
        fonctionnement=ENREGISTREMENT_SEQUENCE;
        printf("fonct:%d\n",fonctionnement);
        printf("enregistrement de sequence\n");
      }
      else if (tab_seq[position_menu]!=NULL){
        printf("je suis censer lire  une sequence\n");
        lire_sequence(tab_seq[position_menu]);
      }
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
}

