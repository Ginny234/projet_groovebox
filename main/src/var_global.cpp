#include "var_global.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2s_in;         //xy=3005.3335876464844,174.6666774749756
AudioRecordQueue         queue1;         //xy=3091.3335876464844,334.6666774749756
AudioPlaySdWav           playSdWav7;     //xy=3331.33349609375,489.6666564941406
AudioPlaySdWav           playSdWav8;     //xy=3349.33349609375,532.6666564941406
AudioPlaySdWav           playSdWav4;     //xy=3412.33349609375,658.6666564941406
AudioPlaySdWav           playSdWav3;     //xy=3426.33349609375,611.6666564941406
AudioPlaySdWav           playSdWav1;     //xy=3477.33349609375,360.6666564941406
AudioPlaySdWav           playSdWav2;     //xy=3479.33349609375,413.6666564941406
AudioPlaySdWav           playSdWav5;     //xy=3518.33349609375,485.6666564941406
AudioPlaySdWav           playSdWav6;     //xy=3522.33349609375,550.6666564941406
AudioMixer4              mixer2;         //xy=3663.33349609375,658.6666564941406
AudioMixer4              mixer1;         //xy=3700.33349609375,386.6666564941406
AudioMixer4              mixer4;         //xy=3711.33349609375,593.6666564941406
AudioMixer4              mixer3;         //xy=3717.33349609375,490.6666564941406
AudioPlaySdRaw           playRaw1;       //xy=3837.333610534668,458.6666946411133
AudioMixer4              mixer6;         //xy=3860.33349609375,621.6666564941406
AudioMixer4              mixer5;         //xy=3878.33349609375,427.6666564941406
AudioMixer4              mixer7;         //xy=3958.33349609375,525.6666564941406
AudioMixer4              mixer9; //xy=4000.6671104431152,460.66669845581055
AudioFilterStateVariable filter1;        //xy=4156.33349609375,298.6666564941406
AudioEffectReverb        reverb1;        //xy=4188.3333740234375,395.66669845581055
AudioSynthWaveform       modulator;      //xy=4270.33349609375,235.66665649414062
AudioMixer4              mixer8;         //xy=4291.333377838135,516.6667032241821
AudioEffectMultiply      multiply1;      //xy=4309.33349609375,358.6666564941406
AudioOutputI2S           i2s1;           //xy=4378.33349609375,480.6666564941406
AudioConnection          patchCord1(i2s_in, 1, queue1, 0);
AudioConnection          patchCord44(i2s_in, 0, queue1, 0);
AudioConnection          patchCord2(playSdWav7, 0, mixer4, 0);
AudioConnection          patchCord3(playSdWav7, 1, mixer4, 1);
AudioConnection          patchCord4(playSdWav8, 0, mixer4, 2);
AudioConnection          patchCord5(playSdWav8, 1, mixer4, 3);
AudioConnection          patchCord6(playSdWav4, 0, mixer2, 2);
AudioConnection          patchCord7(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord8(playSdWav3, 0, mixer2, 0);
AudioConnection          patchCord9(playSdWav3, 1, mixer2, 1);
AudioConnection          patchCord10(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord11(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord12(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord13(playSdWav2, 1, mixer1, 3);
AudioConnection          patchCord14(playSdWav5, 0, mixer3, 0);
AudioConnection          patchCord15(playSdWav5, 1, mixer3, 1);
AudioConnection          patchCord16(playSdWav6, 0, mixer3, 2);
AudioConnection          patchCord17(playSdWav6, 1, mixer3, 3);
AudioConnection          patchCord18(mixer2, 0, mixer6, 2);
AudioConnection          patchCord19(mixer2, 0, mixer6, 3);
AudioConnection          patchCord20(mixer1, 0, mixer5, 0);
AudioConnection          patchCord21(mixer1, 0, mixer5, 1);
AudioConnection          patchCord22(mixer4, 0, mixer6, 0);
AudioConnection          patchCord23(mixer4, 0, mixer6, 1);
AudioConnection          patchCord24(mixer3, 0, mixer5, 2);
AudioConnection          patchCord25(mixer3, 0, mixer5, 3);
AudioConnection          patchCord26(playRaw1, 0, mixer9, 0);
AudioConnection          patchCord43(playRaw1, 0, mixer9, 3);
AudioConnection          patchCord27(mixer6, 0, mixer7, 2);
AudioConnection          patchCord28(mixer6, 0, mixer7, 3);
AudioConnection          patchCord29(mixer5, 0, mixer7, 0);
AudioConnection          patchCord30(mixer5, 0, mixer7, 1);
AudioConnection          patchCord31(mixer7, 0, mixer9, 1);
AudioConnection          patchCord32(mixer7, 0, mixer9, 2);
AudioConnection          patchCord33(mixer9, reverb1);
AudioConnection          patchCord34(mixer9, 0, filter1, 0);
AudioConnection          patchCord35(mixer9, 0, filter1, 1);
AudioConnection          patchCord36(mixer9, 0, mixer8, 1);
AudioConnection          patchCord37(filter1, 1, multiply1, 0);
AudioConnection          patchCord38(reverb1, 0, mixer8, 0);
AudioConnection          patchCord39(modulator, 0, multiply1, 1);
AudioConnection          patchCord40(mixer8, 0, i2s1, 0);
AudioConnection          patchCord41(mixer8, 0, i2s1, 1);
AudioConnection          patchCord42(multiply1, 0, mixer8, 2);
AudioControlSGTL5000     sgtl5000_1;     //xy=4053.33349609375,600.6666564941406
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
Bounce boutonRec = Bounce(PIN_BOUTON_REC, 15);
Bounce bouton_effets = Bounce(11, 15);
//Bounce bouton_reset = Bounce(13, 15);

//autres variables
etat fonctionnement;
effet effet_actif;
int position_menu=0;
sequence* tab_seq[NBR_SEQUENCES];
float volume_courant=1.0f;  // Volume initial entre 0 et 1
unsigned long debut_attente;
unsigned long fin_attente;