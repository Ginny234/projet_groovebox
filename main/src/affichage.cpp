#include "affichage.h"

void affichage_menu(int position_actuelle){
  display.setCursor(MARGE_HMIN, 0);
  //display.print("test\n");
  //display.display();
  for(int i=0; i!=NBR_SEQUENCES; i++){
    if(i==position_actuelle){
      display.print("->");
    }
    display.print("Sequence\n");
  }
  //display.display();
}

void affichage_sample(int id_sample){
  //à changer si on veut afficher des icones
  //char* id;
  //sprintf("Sample jouée: %d", id);
  //display.setCursor(SCREEN_HEIGHT/2/*-strlen(id)/2*/, SCREEN_WIDTH/*-strlen(id)/2*/);
  display.setCursor(0, MARGE_HMIN);
  display.print("Sample jouée");
  //display.display();
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
  char* vol;
  char* grp="Groupe Vocodeur\n";
  sprintf(vol, "Vol:%f", volume_courant*100);
  printf(vol);

  //display.setCursor(0, SCREEN_WIDTH-strlen(vol)*10-3);

  //display.print(vol);
  display.setCursor(0, 0);
  display.print("Groupe Vocodeur\n");
  display.display();
}
