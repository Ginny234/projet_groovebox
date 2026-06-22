#include "modifs_son.h"

//anciennes fonctions, utilisés avec des bouton haut et bas
void augmenter_volume(){
  if (volume_courant < VOLUME_MAX){
    volume_courant += VOLUME_STEP;
    if (volume_courant > VOLUME_MAX){
      volume_courant = VOLUME_MAX;
    }
    sgtl5000_1.volume(volume_courant);
    printf("Volume augmente: %.2f\n", volume_courant);
  }
}

void baisser_volume(){
  if (volume_courant > VOLUME_MIN){
    volume_courant -= VOLUME_STEP;
    if (volume_courant < VOLUME_MIN){
      volume_courant = VOLUME_MIN;
    }
    sgtl5000_1.volume(volume_courant);
    printf("Volume baisse: %.2f\n", volume_courant);
  }
}

//une seule fonction pour le setup des mixers pour rendre l'affichage plus lisible
void setup_mixers(){
  mixer1.gain(0, 0.8);
  mixer1.gain(1, 0.8);
  mixer1.gain(2, 0.8);
  mixer1.gain(3, 0.8);

  mixer2.gain(0, 0.8);
  mixer2.gain(1, 0.8);
  mixer2.gain(2, 0.8);
  mixer2.gain(3, 0.8);

  mixer3.gain(0, 0.8);
  mixer3.gain(1, 0.8);
  mixer3.gain(2, 0.8);
  mixer3.gain(3, 0.8);

  mixer4.gain(0, 0.8);
  mixer4.gain(1, 0.8);
  mixer4.gain(2, 0.8);
  mixer4.gain(3, 0.8);
  
  mixer5.gain(0, 0.8);
  mixer5.gain(1, 0.8);
  mixer5.gain(2, 0.8);
  mixer5.gain(3, 0.8);
  
  mixer6.gain(0, 0.8);
  mixer6.gain(1, 0.8);
  mixer6.gain(2, 0.8);
  mixer6.gain(3, 0.8);

  mixer7.gain(0, 0.8);
  mixer7.gain(1, 0.8);
  mixer7.gain(2, 0.8);
  mixer7.gain(3, 0.8);

  mixer8.gain(0, 0);
  mixer8.gain(1, 0.8);
  mixer8.gain(2, 0.8);
  mixer8.gain(3, 0.8);
}

void naviguation_effets(){
    effet_actif=monter_position(effet_actif, 2);
    //entrée 0 -> reverb appliqué à la sortie du mixer 7
    //entrée 1 -> aucun effet appliqué à la sortie du mixer 7
    //entrée 2 -> effet de son robotique appliqué à la sortie du mixer 7
    switch(effet_actif){
      case AUCUN:
        //son sortie ne prend en compte que l'entrée 1 -> pas d'effet
        mixer8.gain(0, 0);
        mixer8.gain(1, 0.8);
        mixer8.gain(2, 0);
        mixer8.gain(3, 0);
        break;
      case REVERB:
        //son sortie ne prend en compte que l'entrée 0...
        mixer8.gain(0, 1.6);
        mixer8.gain(1, 0);
        mixer8.gain(2, 0);
        mixer8.gain(3, 0);
        break;
      case ROBOTIQUE:
        //même chose que les 2 autres effets
        mixer8.gain(0, 0);
        mixer8.gain(1, 0);
        mixer8.gain(2, 1.6);
        mixer8.gain(3, 0);
        break;
      default:
        effet_actif=AUCUN;
        break;
    }
}

void modifs_volume(){
  static long somme = 0;
  static int nb_lectures = 0;

  somme += analogRead(A1);
  nb_lectures++;

  if (nb_lectures >= 16) {
    int val1 = somme / 16;
    somme = 0;
    nb_lectures = 0;

    int val_min = 0;
    int val_max = 4095;
    volume_courant = constrain(map(val1, val_min, val_max, 0, 1000), 0, 1000) / 1000.0;

    sgtl5000_1.volume(volume_courant);
    /*Serial.print("brut A1 = ");
    Serial.print(val1);
    Serial.print("  ->  volume = ");
    Serial.println(volume_courant);*/
  }
}

void fonctionnement_effets(){
  bouton_effets.update();
  if(bouton_effets.fallingEdge()){
    naviguation_effets();
  }
}