#include "sequences.h"

sequence* initia_sequence(int id_sample){
  sequence* nv_seq=malloc(sizeof(sequence));
  nv_seq->id_sample=id_sample;
  nv_seq->suiv=NULL;
  return nv_seq;
}

sequence* ajouter_sequence(sequence* nv_sample, sequence* seq){
  if(seq!=NULL){
    sequence* temp=seq;
    while(temp->suiv!=NULL){
      temp=temp->suiv;
    }
    temp->suiv=nv_sample;
  }
  else{
    return nv_sample;
  }
  return seq;
}

void lire_sequence(sequence* seq){
  sequence* temp=seq;
  while(temp!=NULL){
    printf("%d\n", temp->id_sample);
    fonctionnement_sample();
    switch(temp->id_sample){
    case 0:
      playMem4.play(AudioSampleSnare);
      break;
    case 1:
      playMem4.play(AudioSampleTomtom);
      break;
    case 2:
      playMem4.play(AudioSampleHihat);
      //playMem3.play(AudioSampleCashregister);
      break;
  }
  temp=temp->suiv;
  unsigned long debut_attente=millis();
  while(millis()-debut_attente<400){
    fonctionnement_sample();
  }
  printf("yayyyy\n");
    //delay(400);
    //temp=temp->suiv;
  }
}