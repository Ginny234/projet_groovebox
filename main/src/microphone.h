#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// Pin configuration
#define PIN_BOUTON_REC 0

// Audio objects
extern AudioInputI2S      i2s_in;
extern AudioRecordQueue   queue1;
extern AudioPlaySdRaw     playRaw1;
extern AudioOutputI2S     i2s_out;
extern AudioControlSGTL5000 sgtl5000_1;

// Button
extern Bounce boutonRec;

// State variables
extern bool recording;
extern bool boutonEnfonce;
extern bool appuiLongDejaDeclenche;

// File handle
extern File frec;

// Timestamps
extern unsigned long startTime;
extern unsigned long appuiDebut;

// Microphone functions
void setupMicrophone();
void updateMicrophone();
void demarrerEnregistrement();
void arreterEnregistrementEtLire();

#endif // MICROPHONE_H
