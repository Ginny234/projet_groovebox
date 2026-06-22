#include "samples.h"
void lire_sample(int id){
  //lecture des samples par des playSdWav différent 
  //-> permet d'avoir plusieurs sample se jouant en simultané
  //-> permet de facilement distingué quels sample sont jouée pour l'affichage
  switch(id){
    case 0:
      playSdWav1.play("SnareDrum.WAV");
      break;
    case 1:
      playSdWav2.play("Hihat.WAV");
      break;
    case 2:
      playSdWav3.play("TomTom.WAV");
      break;
    case 3:
      playSdWav4.play("Cymbal.WAV");
      break;
    case 4:
      playSdWav5.play("Gong.WAV");
      break;
    case 5:
      playSdWav6.play("Misc.WAV");
      break;
    case 6:
      playSdWav7.play("CashRegister.WAV");
    default:
      break;
  }
}

void lire_sample_sequence(int id){
  char* nom_fichier[NBR_BOUTONS_SON]={"SnareDrum.WAV","Hihat.WAV", "TomTom.WAV", "Cymbal.WAV", "Gong.WAV", "Misc.WAV", "CashRegister.WAV"};
  //boucle for qui parcours le tableau des sons à la recherche de celui à jouer
  for(int i=0; i!=NBR_BOUTONS_SON; i++){
    if(i==id){
      //PlaySdWav dédiée à la lectures des séquences -> On peut jouer des sample par dessus
      playSdWav8.play(nom_fichier[i]);
    }
  }
}

void fonctionnement_sample(){
  //parcours tableau de tous les boutons de son (déclaré et définis dans var_global)
  //les update et si ils sont appuyé joue le son associé
  for(int i=0; i!=NBR_BOUTONS_SON;i++){
    tab_boutons_son[i].update();
    if(tab_boutons_son[i].fallingEdge()){
      lire_sample(i);
    }
  }
}
