#ifndef VAR_GLOBAL_H
#define VAR_GLOBAL_H

#include "struct.h"

// GUItool: begin automatically generated code
extern AudioPlayMemory          playMem3;  //xy=220.33332061767578,352.333309173584
extern AudioPlayMemory          playMem2;       //xy=244.3333282470703,293.3333282470703
extern AudioPlayMemory          playMem4; //xy=246.33330535888672,411.3333387374878
extern AudioPlayMemory          playMem1;       //xy=257.3333282470703,207.3333282470703
extern AudioMixer4              mixer1;         //xy=471.3333282470703,217.3333282470703
extern AudioEffectGranular      granular1;
extern AudioOutputI2S           i2s1;           //xy=671.3333282470703,240.3333282470703
extern AudioConnection          patchCord1;
extern AudioConnection          patchCord2;
extern AudioConnection          patchCord3;
extern AudioConnection          patchCord4;
extern AudioConnection          patchCord5;
extern AudioConnection          patchCord6;
extern AudioConnection          patchCord7;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=395.3333282470703,341.3333282470703
// GUItool: end automatically generated code

extern Adafruit_SSD1306 display;

// Bounce objects to read pushbuttons 
extern Bounce button0;
extern Bounce button1;  // 15 ms debounce time
extern Bounce button2;
extern Bounce bouton_sequence;
extern Bounce bouton_haut;
extern Bounce bouton_bas;
extern Bounce bouton_ok;

//autres variables
extern etat fonctionnement;
extern int position_menu;
extern sequence* tab_seq[NBR_SEQUENCES];
extern float volume_courant;  // Volume initial entre 0 et 1
extern float pitch_courant;
extern int pitch_brut_courant;

#define GRANULAR_MEMORY_SIZE 24000
extern int16_t granularMemory[GRANULAR_MEMORY_SIZE];
#endif