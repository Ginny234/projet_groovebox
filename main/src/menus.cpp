#include "menus.h"

//monter et baisser position utiliser pour le menu et les effets
int baisser_position(int position){
  if (position--<=0){
    return 0;
  }
  return position--;
}

int monter_position(int position, int max){
  if (position++>=max){
    return 0;
  }
  return position++;
}

void reset(){
  supprimer_sequences(tab_seq);
  SD.remove("RECORD.RAW");
}