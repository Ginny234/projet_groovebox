#include "var_global.h"

// GUItool: begin automatically generated code
AudioPlayMemory          playMem3;  //xy=220.33332061767578,352.333309173584
AudioPlayMemory          playMem2;       //xy=244.3333282470703,293.3333282470703
AudioPlayMemory          playMem4; //xy=246.33330535888672,411.3333387374878
AudioPlayMemory          playMem1;       //xy=257.3333282470703,207.3333282470703
AudioMixer4              mixer1;         //xy=471.3333282470703,217.3333282470703
AudioEffectGranular      granular1;
AudioOutputI2S           i2s1;           //xy=671.3333282470703,240.3333282470703
AudioConnection          patchCord1(playMem3, 0, mixer1, 2);
AudioConnection          patchCord2(playMem2, 0, mixer1, 1);
AudioConnection          patchCord3(playMem4, 0, mixer1, 3);
AudioConnection          patchCord4(playMem1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, granular1, 0);
AudioConnection          patchCord6(granular1, 0, i2s1, 0);
AudioConnection          patchCord7(granular1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=395.3333282470703,341.3333282470703
// GUItool: end automatically generated code

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bounce objects to read pushbuttons 
Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);  // 15 ms debounce time
Bounce button2 = Bounce(2, 15);
Bounce bouton_sequence = Bounce(3, 15);
Bounce bouton_haut = Bounce(4, 15);
Bounce bouton_bas = Bounce(5, 15);
Bounce bouton_ok = Bounce(6, 15);

//autres variables
etat fonctionnement;
int position_menu=0;
sequence* tab_seq[NBR_SEQUENCES];
float volume_courant=1.0f;  // Volume initial entre 0 et 1
float pitch_courant = 1.0f;
int pitch_brut_courant = 0;
int16_t granularMemory[GRANULAR_MEMORY_SIZE];