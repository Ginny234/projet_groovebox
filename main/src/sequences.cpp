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

void supprimer_sequences(sequence* seq[NBR_SEQUENCES]){
  for(int i=0; i!=NBR_SEQUENCES; i++){
    if(seq[i]!=NULL){
      while(seq[i]!=NULL){
        sequence* temp=seq[i];
        seq[i]=seq[i]->suiv;
        free(temp);
      }
    }
  }
}

void sauvegarder_sequences(sequence* seq[NBR_SEQUENCES]){
  printf("je sauvergarde les séquences...\n");
  File fichier=SD.open("sequences.TXT", FILE_WRITE);
  if(fichier!=NULL){
    for(int i=0; i!=NBR_SEQUENCES; i++){
      if(seq[i]!=NULL){
        char ligne[16];
        sprintf(ligne, "sequence %d\n", i);
        fichier.println(ligne);
        sequence* temp=seq[i];
        while(temp!=NULL){
          sprintf(ligne, "%d\n", temp->id_sample);
          fichier.println(ligne);
          temp=temp->suiv;
        }
      }
    }
  }
  fichier.close();
}

/*sequence* lire_fichier_sequence(File fichier){
  char lettre_ou_num=fgetc(fichier);
  int id;
  sequence* nv_seq;
  while(lettre_ou_num>='0' || lettre_ou_num<='9' ){ //si c'est un chiffre
    fseek(fichier, -1, SEEK_CUR);
    fscanf(fichier,"%d\n",&id);
    nv_seq=ajouter_sequence(nv_seq,initia_sequence(id));
    lettre_ou_num=fgetc(fichier);
  }
  return nv_seq;
}

sequence* lire_fichier_tab_sequences(){
  File fichier=SD.open("sequences.txt", FILE_WRITE);
  while(fgetc(fichier)!=EOF){
    int position_tab;
    fscanf(fichier, "sequence %d\n", position_tab);
    if(0<=position_tab<=4){
      position_tab=0;
    }
    tab_seq[position_tab]=lire_fichier_sequence(fichier);
  }
}*/
