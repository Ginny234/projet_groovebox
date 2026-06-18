#include "menus.h"

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
  SD.remove("REC.RAW");
}