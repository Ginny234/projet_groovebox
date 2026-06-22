#include "sequences.h"

//utilisation de listes pour les séquences 
//-> pas limites de nombre de samples dans une séquence

sequence* initia_sequence(int id_sample){
  sequence* nv_seq=malloc(sizeof(sequence));
  nv_seq->id_sample=id_sample;
  nv_seq->suiv=NULL;
  return nv_seq;
}

sequence* ajouter_sequence(sequence* nv_sample, sequence* seq){
  //liste non vide
  if(seq!=NULL){
    sequence* temp=seq;
    while(temp->suiv!=NULL){
      temp=temp->suiv;
    }
    temp->suiv=nv_sample;
  }
  //premier élément
  else{
    return nv_sample;
  }
  return seq;
}

void lire_sequence(sequence* seq){
  bool sortie=false;
  do{ //joue la séquence en entier au moins une fois
    bouton_ok.update();
    sequence* temp=seq;
    while(temp!=NULL){
      //lecture de la bonne sample en fonction de l'id
      lire_sample_sequence(temp->id_sample);

      temp=temp->suiv;
      unsigned long debut_attente=millis();
      
      //attends 4 secondes 
      while(millis()-debut_attente<400){
        //peut quand même jouer des sample et changer le volume et les effets pendant l'attente
        fonctionnement_sample();
        fonctionnement_effets();
        modifs_volume();

        //si on appuie sur ok, doit s'arrêter
        bouton_ok.update();
        if(bouton_ok.fallingEdge()){
          sortie=true;
        }
      }
    }
  }while(bouton_ok.fallingEdge()==false && sortie==false);
}

void supprimer_sequences(sequence* seq[NBR_SEQUENCES]){
  //parcours le tableau et suppremier les séquence
  for(int i=0; i!=NBR_SEQUENCES; i++){
    if(seq[i]!=NULL){
      while(seq[i]!=NULL){
        sequence* temp=seq[i];
        seq[i]=seq[i]->suiv;
        free(temp);
      }
    }
  }
  //efface le fichier texte pour la persistence
  SD.remove("sequences.TXT");
}

void sauvegarder_sequences(sequence* seq[NBR_SEQUENCES]){
  printf("je sauvergarde les séquences...\n");

  SD.remove("sequences.TXT");
  File fichier=SD.open("sequences.TXT", FILE_WRITE);

  if(fichier!=NULL){
    //parcours du tableau
    for(int i=0; i!=NBR_SEQUENCES; i++){
      if(seq[i]!=NULL){
        //la séquence existe -> on précise quel était sa place dans le tableau
        char ligne[16];
        sprintf(ligne, "sequence %d", i);
        fichier.println(ligne);
        
        //on parcours la liste et écris l'id des sample de la séquence dans l'ordre
        sequence* temp=seq[i];
        while(temp!=NULL){
          sprintf(ligne, "%d", temp->id_sample);
          fichier.println(ligne);
          temp=temp->suiv;
        }
      }
    }
  }
  fichier.close();
}

void lire_fichier_sequence(){
  File fichier=SD.open("sequences.TXT", FILE_READ);
  if(fichier!=NULL){
    char ligne[21];
    int position_tab=0;

    //on lit le fichier ligne par ligne
    while(fichier.available()){
      int nbr_cara =fichier.readBytesUntil('\n', ligne,20 );
      ligne[nbr_cara]='\0';
      
      //si elle commence par s, c'est qu'on précise la place d'une séquence dans le tableau
      if (ligne[0]=='s'){
        sscanf(ligne, "sequence %d\n", &position_tab); //on change donc position tab pour l'enregister ici
      }
      else{ //sinon, on lisait quelles samples était dans une séquence
        int id;
        if(position_tab>4 || position_tab<0){
          position_tab=0;
        }
        sscanf(ligne, "%d\n", &id);
        //on a initialise et ajoute dans la sample à la séquence
        tab_seq[position_tab]=ajouter_sequence(tab_seq[position_tab], initia_sequence(id));
      }
    }
  }
}

}
