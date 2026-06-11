#include "affichage.h"

void affichage_menu(int position_actuelle){
  display.setCursor(0, 10);
  for(int i=0; i!=NBR_SEQUENCES; i++){
    if(i==position_actuelle){
      display.print("->");
    }
    /*char* nom;
    sprintf(nom,"Sequence %d", i);*/
    display.print("Sequence");
    if(tab_seq[i]==NULL){
        display.print("- Vide");
    }
    display.print("\n");
  }
}

void affichage_sample(int id_sample){
    //à changer si on veut afficher des icones
  char id[32];
  snprintf(id, sizeof(id), "Sample %d", id_sample+1);
    printf("%s\n",id);
    display.setCursor(0, 0);
    display.print(id);
}

void affichage_normal(){
  if(playMem1.isPlaying()){
    affichage_sample(0);
  }
  if(playMem2.isPlaying()){
    affichage_sample(1);
  }
    if(playMem3.isPlaying()){
    affichage_sample(2);
  }
}


void affichage_base(){//tous menus compris, afficher absolument TOUT le temps
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
