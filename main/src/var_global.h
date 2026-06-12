#ifndef VAR_GLOBAL_H
#define VAR_GLOBAL_H

#include "struct.h"

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
extern AudioPlayMemory          playMem3;  //xy=220.33332061767578,352.333309173584
extern AudioPlayMemory          playMem5; //xy=238.3333511352539,514.3333339691162
extern AudioPlayMemory          playMem2;       //xy=244.3333282470703,293.3333282470703
extern AudioPlayMemory          playMem4; //xy=246.33330535888672,411.3333387374878
extern AudioPlayMemory          playMem1;       //xy=257.3333282470703,207.3333282470703
extern AudioPlayMemory          playMem6; //xy=381.3333435058594,507.3333320617676
extern AudioMixer4              mixer1;         //xy=467.33333587646484,212.33333778381348
extern AudioPlayMemory          playMem8; //xy=516.3333740234375,507.3332996368408
extern AudioMixer4              mixer2;         //xy=523.3333435058594,427.3333320617676
extern AudioPlayMemory          playMem7; //xy=658.3333778381348,508.3333320617676
extern AudioMixer4              mixer3;         //xy=667.3333282470703,268.3333282470703
extern AudioOutputI2S           i2s1;           //xy=886.333381652832,287.33330059051514
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioConnection          patchCord8;
extern AudioConnection          patchCord9;
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord11;
extern AudioConnection          patchCord12;
extern AudioConnection          patchCord13;
extern AudioConnection          patchCord14;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=958.3333282470703,392.33330059051514
// GUItool: end automatically generated code
extern Adafruit_SSD1306 display;

// Bounce objects to read pushbuttons 
extern Bounce button0;
extern Bounce button1;  // 15 ms debounce time
extern Bounce button2;
extern Bounce button3;
extern Bounce button4;
extern Bounce button5;
extern Bounce button6;
extern Bounce bouton_sequence;
extern Bounce bouton_ok;
extern Bounce tab_boutons_son[NBR_BOUTONS_SON];

//autres variables
extern etat fonctionnement;
extern int position_menu;
extern sequence* tab_seq[NBR_SEQUENCES];
extern float volume_courant;  // Volume initial entre 0 et 1
#endif