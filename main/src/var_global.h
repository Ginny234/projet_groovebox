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
extern AudioPlaySdWav           playSdWav7; //xy=236.3333511352539,281.66666889190674
extern AudioPlaySdWav           playSdWav8; //xy=254.3333511352539,324.6666851043701
extern AudioPlaySdWav           playSdWav4; //xy=317.33333587646484,450.6666650772095
extern AudioPlaySdWav           playSdWav3; //xy=331.3333435058594,403.6666660308838
extern AudioPlaySdWav           playSdWav1;     //xy=380.6666488647461,162.3333396911621
extern AudioPlaySdWav           playSdWav2; //xy=384.33333587646484,205.6666841506958
extern AudioPlaySdWav           playSdWav5; //xy=423.33333587646484,277.66668701171875
extern AudioPlaySdWav           playSdWav6; //xy=427.33333587646484,342.6666889190674
extern AudioMixer4              mixer2;         //xy=568.3333435058594,450.333345413208
extern AudioMixer4              mixer1;         //xy=605.3333435058594,178.3333396911621
extern AudioMixer4              mixer4; //xy=616.3333740234375,385.66668701171875
extern AudioMixer4              mixer3;         //xy=622.3333511352539,282.3333320617676
extern AudioMixer4              mixer6; //xy=765.6666679382324,413.33333015441895
extern AudioMixer4              mixer5; //xy=783.6666030883789,219.33332061767578
extern AudioMixer4              mixer7; //xy=866.6666641235352,322.33333015441895
extern AudioOutputI2S           i2s1;           //xy=1041.3333587646484,321.33330154418945
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