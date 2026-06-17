#include "affichage.h"

void affichage_menu(int position_actuelle){
  display.setCursor(0, 10);
  for(int i=0; i!=NBR_SEQUENCES; i++){
    if(i==position_actuelle){
      display.print("->");
    }
    char nom[15];
    sprintf(nom,"Sequence %d", i+1);
    //printf("%s", nom);
    display.print(nom);
    if(tab_seq[i]==NULL){
        display.print("- Vide");
    }
    display.print("\n");
  }
  display.print("Maintenir ok pour modifier\n");
}

void affichage_sample(int id_sample){
    //à changer si on veut afficher des icones
    char id[10];
    sprintf(id,"Sample %d", id_sample+1);
    //printf("%s\n",id);
    display.setCursor(0, 0);
    display.print(id);
}

void affichage_normal(){
  if(playSdWav1.isPlaying()){
    affichage_sample(0);
  }
  else if(playSdWav2.isPlaying()){
    affichage_sample(1);
  }
  else if(playSdWav3.isPlaying()){
    affichage_sample(2);
  }
  else if(playSdWav4.isPlaying()){
    affichage_sample(3);
  }
  else if(playSdWav5.isPlaying()){
    affichage_sample(4);
  }
  else if(playSdWav6.isPlaying()){
    affichage_sample(5);
  }
  else if(playSdWav7.isPlaying()){
    affichage_sample(6);
  }
}

void affichage_base(){//tous menus compris, afficher absolument TOUT le temps
  //printf("AFFICHAGE BASE\n");
  char vol[10];
  sprintf(vol, "Vol:%d", (int)(volume_courant*100));
  //printf(vol);

  //display.setCursor(0, SCREEN_WIDTH-strlen(vol)*10-3);

  //display.print(vol);
  display.setCursor(SCREEN_WIDTH/2-strlen("Groupe Vocodeur")*11/4, SCREEN_HEIGHT-8);
  display.print("Groupe Vocodeur\n");
  display.setCursor(SCREEN_WIDTH-strlen(vol)*6, 0);
  display.print(vol);
  display.display();
}

void affichage_enregistrement(){
    display.clearDisplay();
    affichage_normal();
    display.setCursor(SCREEN_WIDTH/2-strlen("Enregistrement")*11/4, SCREEN_HEIGHT-35);
    display.print("Enregistrement\n");
    display.setCursor(0, SCREEN_HEIGHT-25);
    display.print("Appuyez sur ok pour \nterminer");
}