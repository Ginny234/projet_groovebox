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
    case 3:
      playMem4.play(AudioSampleKick);
      break;
    case 4:
      playMem5.play(AudioSampleGong);
      break;
    case 5:
      playMem6.play(AudioSampleCashregister);
      break;
    case 6:
      playMem7.play(AudioSampleHihat);
    default:
      break;
  }
}

void lire_sample_sequence(int id){
    switch(id){
    case 0:
      playMem8.play(AudioSampleSnare);
      break;
    case 1:
      playMem8.play(AudioSampleTomtom);
      break;
    case 2:
      playMem8.play(AudioSampleHihat);
      break;
    case 3:
      playMem8.play(AudioSampleKick);
      break;
    case 4:
      playMem8.play(AudioSampleGong);
      break;
    case 5:
      playMem8.play(AudioSampleCashregister);
      break;
    case 6:
      playMem8.play(AudioSampleHihat);
    default:
      break;
  }
}

void fonctionnement_sample(){
  for(int i=0; i!=NBR_BOUTONS_SON;i++){
    tab_boutons_son[i].update();
    if(tab_boutons_son[i].fallingEdge()){
      lire_sample(i);
    }
  }
  /*if (button0.fallingEdge()) {
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
  }*/
}
