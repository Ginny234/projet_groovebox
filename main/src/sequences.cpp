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
  bool sortie=false;
  do{
    bouton_ok.update();
    printf("okkkk\n");
    sequence* temp=seq;
    while(temp!=NULL){
      printf("%d\n", temp->id_sample);
      //fonctionnement_sample();
      lire_sample_sequence(temp->id_sample);
    
    
    temp=temp->suiv;
    unsigned long debut_attente=millis();
    while(millis()-debut_attente<400){
      fonctionnement_sample();
      bouton_ok.update();
      if(bouton_ok.fallingEdge()){
        sortie=true;
      }
    }
    printf("yayyyy\n");
      //delay(400);
      //temp=temp->suiv;
    }
  }while(bouton_ok.fallingEdge()==false && sortie==false);
}