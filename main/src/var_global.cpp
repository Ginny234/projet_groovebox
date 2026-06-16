#include "var_global.h"

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav7; //xy=236.3333511352539,281.66666889190674
AudioPlaySdWav           playSdWav8; //xy=254.3333511352539,324.6666851043701
AudioPlaySdWav           playSdWav4; //xy=317.33333587646484,450.6666650772095
AudioPlaySdWav           playSdWav3; //xy=331.3333435058594,403.6666660308838
AudioPlaySdWav           playSdWav1;     //xy=380.6666488647461,162.3333396911621
AudioPlaySdWav           playSdWav2; //xy=384.33333587646484,205.6666841506958
AudioPlaySdWav           playSdWav5; //xy=423.33333587646484,277.66668701171875
AudioPlaySdWav           playSdWav6; //xy=427.33333587646484,342.6666889190674
AudioMixer4              mixer2;         //xy=568.3333435058594,450.333345413208
AudioMixer4              mixer1;         //xy=605.3333435058594,178.3333396911621
AudioMixer4              mixer4; //xy=616.3333740234375,385.66668701171875
AudioMixer4              mixer3;         //xy=622.3333511352539,282.3333320617676
AudioMixer4              mixer6; //xy=765.6666679382324,413.33333015441895
AudioMixer4              mixer5; //xy=783.6666030883789,219.33332061767578
AudioMixer4              mixer7; //xy=866.6666641235352,322.33333015441895
AudioOutputI2S           i2s1;           //xy=1041.3333587646484,321.33330154418945
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
AudioConnection          patchCord25(mixer6, 0, mixer7, 2);
AudioConnection          patchCord26(mixer6, 0, mixer7, 3);
AudioConnection          patchCord27(mixer5, 0, mixer7, 0);
AudioConnection          patchCord28(mixer5, 0, mixer7, 1);
AudioConnection          patchCord29(mixer7, 0, i2s1, 0);
AudioConnection          patchCord30(mixer7, 0, i2s1, 1);
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