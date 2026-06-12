#include "var_global.h"

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem3;  //xy=220.33332061767578,352.333309173584
AudioPlayMemory          playMem5; //xy=238.3333511352539,514.3333339691162
AudioPlayMemory          playMem2;       //xy=244.3333282470703,293.3333282470703
AudioPlayMemory          playMem4; //xy=246.33330535888672,411.3333387374878
AudioPlayMemory          playMem1;       //xy=257.3333282470703,207.3333282470703
AudioPlayMemory          playMem6; //xy=381.3333435058594,507.3333320617676
AudioMixer4              mixer1;         //xy=467.33333587646484,212.33333778381348
AudioPlayMemory          playMem8; //xy=516.3333740234375,507.3332996368408
AudioMixer4              mixer2;         //xy=523.3333435058594,427.3333320617676
AudioPlayMemory          playMem7; //xy=658.3333778381348,508.3333320617676
AudioMixer4              mixer3;         //xy=667.3333282470703,268.3333282470703
AudioOutputI2S           i2s1;           //xy=886.333381652832,287.33330059051514
AudioConnection          patchCord1(playMem3, 0, mixer1, 2);
AudioConnection          patchCord2(playMem5, 0, mixer2, 0);
AudioConnection          patchCord3(playMem2, 0, mixer1, 1);
AudioConnection          patchCord4(playMem4, 0, mixer1, 3);
AudioConnection          patchCord5(playMem1, 0, mixer1, 0);
AudioConnection          patchCord6(playMem6, 0, mixer2, 1);
AudioConnection          patchCord7(mixer1, 0, mixer3, 0);
AudioConnection          patchCord8(mixer1, 0, mixer3, 2);
AudioConnection          patchCord9(playMem8, 0, mixer2, 3);
AudioConnection          patchCord10(mixer2, 0, mixer3, 3);
AudioConnection          patchCord11(mixer2, 0, mixer3, 1);
AudioConnection          patchCord12(playMem7, 0, mixer2, 2);
AudioConnection          patchCord13(mixer3, 0, i2s1, 0);
AudioConnection          patchCord14(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=958.3333282470703,392.33330059051514
// GUItool: end automatically generated code

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bounce objects to read pushbuttons 
Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);  // 15 ms debounce time
Bounce button2 = Bounce(2, 15);
Bounce button3 = Bounce(3, 15);
Bounce button4 = Bounce(4, 15);
Bounce button5 = Bounce(5, 15);
Bounce button6 = Bounce(6, 15);
Bounce bouton_sequence = Bounce(9, 15);
Bounce bouton_ok = Bounce(SW, 15);
Bounce tab_boutons_son[NBR_BOUTONS_SON]={button0, button1, button2, button3, button4, button5, button6};

//autres variables
etat fonctionnement;
int position_menu=0;
sequence* tab_seq[NBR_SEQUENCES];
float volume_courant=1.0f;  // Volume initial entre 0 et 1