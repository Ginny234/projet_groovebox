#include "sequences.h"

sequence* initia_sequence(int id_sample){
  sequence* nv_seq=new sequence;
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
    lire_sample(temp->id_sample);
    delay(400);
    temp=temp->suiv;
  }
}