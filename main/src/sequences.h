#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "struct.h"
#include "var_global.h"
#include "samples.h"
#include "modifs_son.h"

sequence* initia_sequence(int id_sample);
sequence* ajouter_sequence(sequence* nv_sample, sequence* seq);
void lire_sequence(sequence* seq);
void supprimer_sequences(sequence* seq[NBR_SEQUENCES]);
sequence* lire_fichier_tab_sequences();
void lire_fichier_sequence();
void sauvegarder_sequences(sequence* seq[NBR_SEQUENCES]);
#endif