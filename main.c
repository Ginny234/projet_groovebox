#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NBR_SEQUENCES 4
#define NBR_BOUTONS 7

typedef struct sequence sequence;
struct sequence{
  int id_sample;
  sequence* suiv;
};

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

void lire_sample(int id){
  switch(id){
    case 0:
      //playMem1.play(AudioSampleSnare);
    case 1:
      //playMem2.play(AudioSampleTomtom);
    case 2:
      //playMem3.play(AudioSampleHihat);
  }
}

void lire_sequence(sequence* seq){
  sequence* temp=seq;
  while(temp!=NULL){
    printf("%d\n", temp->id_sample);
    //lire_sample(temp->id_sample);
    temp=temp->suiv;
  }
}

int main(){
  printf("PK TU MARCHE PAS\n");
  sequence* tab_seq[NBR_SEQUENCES];

  for(int i=0; i!=NBR_SEQUENCES; i++){
    tab_seq[i]=NULL;
  }

  int position_menu=0;
  
  tab_seq[position_menu]=ajouter_sequence(initia_sequence(2), tab_seq[position_menu]);
  tab_seq[position_menu]=ajouter_sequence(initia_sequence(2), tab_seq[position_menu]);
  tab_seq[position_menu]=ajouter_sequence(initia_sequence(1), tab_seq[position_menu]);

  printf("lire sequence\n");
  lire_sequence(tab_seq[position_menu]);
  return 0;
}