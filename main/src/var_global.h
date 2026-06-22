#ifndef VAR_GLOBAL_H
#define VAR_GLOBAL_H

#include "struct.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

extern AudioInputI2SQuad        i2s_in;
extern AudioRecordQueue         queue1;
extern AudioPlaySdRaw           playRaw1;
extern AudioOutputI2S           i2s1;

extern AudioPlaySdWav           playSdWav7;
extern AudioPlaySdWav           playSdWav8;
extern AudioPlaySdWav           playSdWav4;
extern AudioPlaySdWav           playSdWav3;
extern AudioPlaySdWav           playSdWav1;
extern AudioPlaySdWav           playSdWav2;
extern AudioPlaySdWav           playSdWav5;
extern AudioPlaySdWav           playSdWav6;

extern AudioMixer4              mixer2;
extern AudioMixer4              mixer1;
extern AudioMixer4              mixer4;
extern AudioMixer4              mixer3;
extern AudioMixer4              mixer6;
extern AudioMixer4              mixer5;
extern AudioMixer4              mixer7;
extern AudioMixer4              mixerFinal;

extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord10;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioConnection          patchCord15;
extern AudioConnection          patchCord16;
extern AudioConnection          patchCord17;
extern AudioConnection          patchCord18;
extern AudioConnection          patchCord19;
extern AudioConnection          patchCord20;
extern AudioConnection          patchCord21;
extern AudioConnection          patchCord22;
extern AudioConnection          patchCord23;
extern AudioConnection          patchCord24;
extern AudioConnection          patchCord25;
extern AudioConnection          patchCord26;
extern AudioConnection          patchCord27;
extern AudioConnection          patchCord28;
extern AudioConnection          patchCord29;
extern AudioConnection          patchCord30;
extern AudioConnection          patchCord31;
extern AudioConnection          patchCord32;

extern AudioControlSGTL5000     sgtl5000_1;

extern Adafruit_SSD1306 display;

extern Bounce button0;
extern Bounce button1;
extern Bounce button2;
extern Bounce button3;
extern Bounce button4;
extern Bounce button5;
extern Bounce button6;
extern Bounce bouton_sequence;
extern Bounce bouton_ok;
extern Bounce boutonRec;

extern Bounce tab_boutons_son[NBR_BOUTONS_SON];

extern etat fonctionnement;
extern int position_menu;
extern sequence* tab_seq[NBR_SEQUENCES];
extern float volume_courant;
extern unsigned long debut_attente;
extern unsigned long fin_attente;

#endif