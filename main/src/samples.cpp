#include "samples.h"
void lire_sample(int id){
  switch(id){
    case 0:
      playMem1.play(AudioSampleSnare);
      break;
    case 1:
      playMem2.play(AudioSampleTomtom);
      break;
    case 2:
      playMem3.play(AudioSampleHihat);
      break;
  }
}

void fonctionnement_sample(){
  button0.update();
  button1.update();
  button2.update();

  if (button0.fallingEdge()) {
    printf("son bouton 1\n");
    lire_sample(0);
  }
  if (button1.fallingEdge()) {
    printf("son bouton 2\n");
    lire_sample(1);
  }
  if (button2.fallingEdge()) {
    printf("son bouton 3\n");
    lire_sample(2);
  }
}
