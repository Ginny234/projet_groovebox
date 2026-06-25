#ifndef VAR_GLOBAL_H
#define VAR_GLOBAL_H

#include "struct.h"

// GUItool: begin automatically generated code
extern AudioInputI2S            i2s_in;         //xy=3005.3335876464844,174.6666774749756
extern AudioRecordQueue         queue1;         //xy=3091.3335876464844,334.6666774749756
extern AudioPlaySdWav           playSdWav7;     //xy=3331.33349609375,489.6666564941406
extern AudioPlaySdWav           playSdWav8;     //xy=3349.33349609375,532.6666564941406
extern AudioPlaySdWav           playSdWav4;     //xy=3412.33349609375,658.6666564941406
extern AudioPlaySdWav           playSdWav3;     //xy=3426.33349609375,611.6666564941406
extern AudioPlaySdWav           playSdWav1;     //xy=3477.33349609375,360.6666564941406
extern AudioPlaySdWav           playSdWav2;     //xy=3479.33349609375,413.6666564941406
extern AudioPlaySdWav           playSdWav5;     //xy=3518.33349609375,485.6666564941406
extern AudioPlaySdWav           playSdWav6;     //xy=3522.33349609375,550.6666564941406
extern AudioMixer4              mixer2;         //xy=3663.33349609375,658.6666564941406
extern AudioMixer4              mixer1;         //xy=3700.33349609375,386.6666564941406
extern AudioMixer4              mixer4;         //xy=3711.33349609375,593.6666564941406
extern AudioMixer4              mixer3;         //xy=3717.33349609375,490.6666564941406
extern AudioPlaySdRaw           playRaw1;       //xy=3837.333610534668,458.6666946411133
extern AudioMixer4              mixer6;         //xy=3860.33349609375,621.6666564941406
extern AudioMixer4              mixer5;         //xy=3878.33349609375,427.6666564941406
extern AudioMixer4              mixer7;         //xy=3958.33349609375,525.6666564941406
extern AudioMixer4              mixer9; //xy=4000.6671104431152,460.66669845581055
extern AudioFilterStateVariable filter1;        //xy=4156.33349609375,298.6666564941406
extern AudioEffectReverb        reverb1;        //xy=4188.3333740234375,395.66669845581055
extern AudioSynthWaveform       modulator;      //xy=4270.33349609375,235.66665649414062
extern AudioMixer4              mixer8;         //xy=4291.333377838135,516.6667032241821
extern AudioEffectMultiply      multiply1;      //xy=4309.33349609375,358.6666564941406
extern AudioOutputI2S           i2s1;           //xy=4378.33349609375,480.6666564941406
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
extern AudioConnection          patchCord33;
extern AudioConnection          patchCord34;
extern AudioConnection          patchCord35;
extern AudioConnection          patchCord36;
extern AudioConnection          patchCord37;
extern AudioConnection          patchCord38;
extern AudioConnection          patchCord39;
extern AudioConnection          patchCord40;
extern AudioConnection          patchCord41;
extern AudioConnection          patchCord42;
extern AudioControlSGTL5000     sgtl5000_1;     //xy=4053.33349609375,600.6666564941406
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
extern Bounce boutonRec;
//extern Bounce bouton_reset;
extern Bounce bouton_effets;

//autres variables
extern etat fonctionnement;
extern effet effet_actif;
extern int position_menu;
extern sequence* tab_seq[NBR_SEQUENCES];
extern float volume_courant;  // Volume initial entre 0 et 1
extern float pitch_courant;
extern int pitch_brut_courant;

#define GRANULAR_MEMORY_SIZE 24000
extern int16_t granularMemory[GRANULAR_MEMORY_SIZE];
extern unsigned long debut_attente;
extern unsigned long fin_attente;
#endif