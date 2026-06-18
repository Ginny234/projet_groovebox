#ifndef SEQUENCES_H
#define SEQUENCES_H

#include "struct.h"
#include "var_global.h"
#include "samples.h"

sequence* initia_sequence(int id_sample);
sequence* ajouter_sequence(sequence* nv_sample, sequence* seq);
void lire_sequence(sequence* seq);
void supprimer_sequences(sequence* seq[NBR_SEQUENCES]);

#endif