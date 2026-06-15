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

  display.setCursor(SCREEN_WIDTH/2-strlen("Groupe Vocodeur")*11/4, SCREEN_HEIGHT-8);
  display.print("Groupe Vocodeur\n");
  
  display.setCursor(SCREEN_WIDTH-strlen(vol)*6, 0);
  display.print(vol);
  
  // Affichage du Pitch
  char pitch_str[20];
  sprintf(pitch_str, "Pitch: %.2f", pitch_courant);
  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(pitch_str);
  display.setTextSize(1);

  char adc_str[16];
  sprintf(adc_str, "A7:%d", pitch_brut_courant);
  display.setCursor(0, 40);
  display.print(adc_str);

  display.display();
}
