#include "var_global.h"

AudioInputI2SQuad i2s_in;
AudioRecordQueue  queue1;
AudioPlaySdRaw    playRaw1;
AudioOutputI2S    i2s1;

AudioConnection patchCord_mic_1(i2s_in, 0, queue1, 0);

AudioPlaySdWav playSdWav7;
AudioPlaySdWav playSdWav8;
AudioPlaySdWav playSdWav4;
AudioPlaySdWav playSdWav3;
AudioPlaySdWav playSdWav1;
AudioPlaySdWav playSdWav2;
AudioPlaySdWav playSdWav5;
AudioPlaySdWav playSdWav6;

AudioMixer4 mixer2;
AudioMixer4 mixer1;
AudioMixer4 mixer4;
AudioMixer4 mixer3;
AudioMixer4 mixer6;
AudioMixer4 mixer5;
AudioMixer4 mixer7;
AudioMixer4 mixerFinal;

AudioConnection patchCord1(playSdWav7, 0, mixer4, 0);
AudioConnection patchCord2(playSdWav7, 1, mixer4, 1);
AudioConnection patchCord3(playSdWav8, 0, mixer4, 2);
AudioConnection patchCord4(playSdWav8, 1, mixer4, 3);

AudioConnection patchCord5(playSdWav4, 0, mixer2, 2);
AudioConnection patchCord6(playSdWav4, 1, mixer2, 3);
AudioConnection patchCord7(playSdWav3, 0, mixer2, 0);
AudioConnection patchCord8(playSdWav3, 1, mixer2, 1);
AudioConnection patchCord9(playSdWav1, 0, mixer1, 0);
AudioConnection patchCord10(playSdWav1, 1, mixer1, 1);
AudioConnection patchCord11(playSdWav2, 0, mixer1, 2);
AudioConnection patchCord12(playSdWav2, 1, mixer1, 3);
AudioConnection patchCord13(playSdWav5, 0, mixer3, 0);
AudioConnection patchCord14(playSdWav5, 1, mixer3, 1);
AudioConnection patchCord15(playSdWav6, 0, mixer3, 2);
AudioConnection patchCord16(playSdWav6, 1, mixer3, 3);

AudioConnection patchCord17(mixer2, 0, mixer6, 2);
AudioConnection patchCord18(mixer2, 0, mixer6, 3);
AudioConnection patchCord19(mixer1, 0, mixer5, 0);
AudioConnection patchCord20(mixer1, 0, mixer5, 1);
AudioConnection patchCord21(mixer4, 0, mixer6, 0);
AudioConnection patchCord22(mixer4, 0, mixer6, 1);
AudioConnection patchCord23(mixer3, 0, mixer5, 2);
AudioConnection patchCord24(mixer3, 0, mixer5, 3);
AudioConnection patchCord25(mixer6, 0, mixer7, 2);
AudioConnection patchCord26(mixer6, 0, mixer7, 3);
AudioConnection patchCord27(mixer5, 0, mixer7, 0);
AudioConnection patchCord28(mixer5, 0, mixer7, 1);

AudioConnection patchCord29(mixer7, 0, mixerFinal, 0);     // samples
AudioConnection patchCord30(playRaw1, 0, mixerFinal, 1);   // lecture micro

AudioConnection patchCord31(mixerFinal, 0, i2s1, 0);
AudioConnection patchCord32(mixerFinal, 0, i2s1, 1);

AudioControlSGTL5000 sgtl5000_1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);
Bounce button2 = Bounce(2, 15);
Bounce button3 = Bounce(3, 15);
Bounce button4 = Bounce(4, 15);
Bounce button5 = Bounce(5, 15);
Bounce button6 = Bounce(6, 15);
Bounce bouton_sequence = Bounce(9, 15);
Bounce bouton_ok = Bounce(SW, 15);

Bounce tab_boutons_son[NBR_BOUTONS_SON] = {
  button0, button1, button2, button3, button4, button5, button6
};

Bounce boutonRec = Bounce(PIN_BOUTON_REC, 15);

etat fonctionnement;
int position_menu = 0;
sequence* tab_seq[NBR_SEQUENCES];
float volume_courant = 1.0f;
unsigned long debut_attente;
unsigned long fin_attente;