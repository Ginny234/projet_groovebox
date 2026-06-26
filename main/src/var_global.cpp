#include "var_global.h"

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav7;     //xy=3674.333251953125,448.33331298828125
AudioPlaySdWav           playSdWav8;     //xy=3692.333251953125,491.33331298828125
AudioPlaySdWav           playSdWav4;     //xy=3755.333251953125,617.3333129882812
AudioPlaySdWav           playSdWav3;     //xy=3769.333251953125,570.3333129882812
AudioPlaySdWav           playSdWav1;     //xy=3820.333251953125,319.33331298828125
AudioPlaySdWav           playSdWav2;     //xy=3822.333251953125,372.33331298828125
AudioPlaySdWav           playSdWav5;     //xy=3861.333251953125,444.33331298828125
AudioPlaySdWav           playSdWav6;     //xy=3865.333251953125,509.33331298828125
AudioMixer4              mixer2;         //xy=4006.333251953125,617.3333129882812
AudioMixer4              mixer1;         //xy=4043.333251953125,345.33331298828125
AudioMixer4              mixer4;         //xy=4054.333251953125,552.3333129882812
AudioMixer4              mixer3;         //xy=4060.333251953125,449.33331298828125
AudioInputI2S            i2s_in;         //xy=4125.833648681641,95.83331871032715
AudioMixer4              mixer6;         //xy=4203.333251953125,580.3333129882812
AudioRecordQueue         queue1;         //xy=4211.833648681641,255.83331871032715
AudioMixer4              mixer5;         //xy=4221.333251953125,386.33331298828125
AudioMixer4              mixer7;         //xy=4267.333625793457,514.3333511352539
AudioPlaySdRaw           playRaw1;       //xy=4348.333377838135,311.3333568572998
AudioMixer4              mixer9;         //xy=4383.333625793457,457.3333492279053
AudioEffectGranular      granular1;      //xy=4550.667125701904,470.66669845581055
AudioFilterStateVariable filter1;        //xy=4703.333633422852,283.3333492279053
AudioEffectReverb        reverb1;        //xy=4735.333633422852,380.3333492279053
AudioSynthWaveform       modulator;      //xy=4817.333633422852,220.33334922790527
AudioMixer4              mixer8;         //xy=4838.333633422852,501.3333492279053
AudioEffectMultiply      multiply1;      //xy=4856.333633422852,343.3333492279053
AudioOutputI2S           i2s1;           //xy=4925.333633422852,465.3333492279053
AudioConnection          patchCord1(playSdWav7, 0, mixer4, 0);
AudioConnection          patchCord2(playSdWav7, 1, mixer4, 1);
AudioConnection          patchCord3(playSdWav8, 0, mixer4, 2);
AudioConnection          patchCord4(playSdWav8, 1, mixer4, 3);
AudioConnection          patchCord5(playSdWav4, 0, mixer2, 2);
AudioConnection          patchCord6(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord7(playSdWav3, 0, mixer2, 0);
AudioConnection          patchCord8(playSdWav3, 1, mixer2, 1);
AudioConnection          patchCord9(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord10(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord11(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord12(playSdWav2, 1, mixer1, 3);
AudioConnection          patchCord13(playSdWav5, 0, mixer3, 0);
AudioConnection          patchCord14(playSdWav5, 1, mixer3, 1);
AudioConnection          patchCord15(playSdWav6, 0, mixer3, 2);
AudioConnection          patchCord16(playSdWav6, 1, mixer3, 3);
AudioConnection          patchCord17(mixer2, 0, mixer6, 2);
AudioConnection          patchCord18(mixer2, 0, mixer6, 3);
AudioConnection          patchCord19(mixer1, 0, mixer5, 0);
AudioConnection          patchCord20(mixer1, 0, mixer5, 1);
AudioConnection          patchCord21(mixer4, 0, mixer6, 0);
AudioConnection          patchCord22(mixer4, 0, mixer6, 1);
AudioConnection          patchCord23(mixer3, 0, mixer5, 2);
AudioConnection          patchCord24(mixer3, 0, mixer5, 3);
AudioConnection          patchCord25(i2s_in, 0, queue1, 0);
AudioConnection          patchCord26(i2s_in, 1, queue1, 0);
AudioConnection          patchCord27(mixer6, 0, mixer7, 2);
AudioConnection          patchCord28(mixer6, 0, mixer7, 3);
AudioConnection          patchCord29(mixer5, 0, mixer7, 0);
AudioConnection          patchCord30(mixer5, 0, mixer7, 1);
AudioConnection          patchCord31(mixer7, 0, mixer9, 1);
AudioConnection          patchCord32(mixer7, 0, mixer9, 2);
AudioConnection          patchCord33(playRaw1, 0, mixer9, 0);
AudioConnection          patchCord34(playRaw1, 0, mixer9, 3);
AudioConnection          patchCord35(mixer9, granular1);
AudioConnection          patchCord36(granular1, 0, filter1, 0);
AudioConnection          patchCord37(granular1, reverb1);
AudioConnection          patchCord38(granular1, 0, mixer8, 1);
AudioConnection          patchCord39(filter1, 1, multiply1, 0);
AudioConnection          patchCord40(reverb1, 0, mixer8, 0);
AudioConnection          patchCord41(modulator, 0, multiply1, 1);
AudioConnection          patchCord42(mixer8, 0, i2s1, 0);
AudioConnection          patchCord43(mixer8, 0, i2s1, 1);
AudioConnection          patchCord44(multiply1, 0, mixer8, 2);
AudioControlSGTL5000     sgtl5000_1;     //xy=4396.333251953125,559.3333129882812
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
Bounce bouton_sequence = Bounce(11, 15);
Bounce bouton_ok = Bounce(SW, 15);
Bounce tab_boutons_son[NBR_BOUTONS_SON]={button0, button1, button2, button3, button4, button5, button6};
Bounce boutonRec = Bounce(PIN_BOUTON_REC, 15);
Bounce bouton_effets = Bounce(9, 15);
Bounce bouton_reset = Bounce(24, 15);

//autres variables
etat fonctionnement;
effet effet_actif;
int position_menu=0;
sequence* tab_seq[NBR_SEQUENCES];
float volume_courant=1.0f;  // Volume initial entre 0 et 1
float pitch_courant = 1.0f;
int pitch_brut_courant = 0;
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
unsigned long debut_attente;
unsigned long fin_attente;
