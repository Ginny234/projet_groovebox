#include "affichage.h"
#include "microphone.h"

void affichage_menu(int position_actuelle){
  display.setCursor(0, 10); //marge pour laisser de la place à l'affichage des samples
  //affichage de 4 lignes pour les 4 séquences du tableau
  for(int i=0; i!=NBR_SEQUENCES; i++){
    //si c'est la séquence sélectionnée, affichage différent
    if(i==position_actuelle){
      display.print("->");
    }
    char nom[15];
    sprintf(nom,"Sequence %d", i+1);
    display.print(nom);
    //affichage précisant si une séquence était déjà à cet emplacement
    if(tab_seq[i]==NULL){
        display.print("- Vide");
    }
    display.print("\n");
  }
  display.print("Maintenir ok pour modifier\n");
}

void affichage_sample(int id_sample){
    char id[10];
    sprintf(id,"Sample %d", id_sample+1);
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

void affichage_base(){//tous menus compris, affiché absolument TOUT le temps
  //pas de display clear pour ne pas effacer les autres affichage, fonction appelée en dernier
  char vol[10];
  sprintf(vol, "Vol:%d", (int)(volume_courant*100));

  //placement au milieu, en bas
  display.setCursor(SCREEN_WIDTH/2-strlen("Groupe Vocodeur")*11/4, SCREEN_HEIGHT-8);
  display.print("Groupe Vocodeur\n");

  //placement en haut à gauche
  display.setCursor(SCREEN_WIDTH-strlen(vol)*6, 0);
  display.print(vol);

  //affichage de l'effet uniquement hors des menus pour eviter qu'il chevauche un autre affichage
  if(fonctionnement==NORMAL){
    char effet[20];
    sprintf(effet, "Effet:%d", effet_actif);

    //placement en haut à gauche, sous le volume
    display.setCursor(SCREEN_WIDTH-strlen(effet)*6, 8);
    display.print(effet);

    display.setCursor(0, SCREEN_HEIGHT - 8*5);
    display.print("Maintenir 'micro' appuye pour lancer un \n enregistrement");
  }
  display.display();
}

void affichage_enregistrement(){ //enregistrement des séquence
    display.clearDisplay();
    affichage_normal(); // affiche les sample jouées lors de l'enregistrement
    display.setCursor(SCREEN_WIDTH/2-strlen("Enregistrement")*11/4, SCREEN_HEIGHT-35);
    display.print("Enregistrement\n");
    display.setCursor(0, SCREEN_HEIGHT-25);
    display.print("Appuyez sur ok pour \nterminer");
}

void affichage_microphone() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Micro");

  display.setCursor(0, 20);

  if (recording) {
    display.print("Enregistrement...");
  }
  else if (playing) {
    display.print("Lecture...");
  }
  else {
    display.print("Pret");
  }

  display.setCursor(0, 40);
  display.print("Appui long: REC");
  display.setCursor(0, 50);
  display.print("Appui court: Lire");

  display.display();
}