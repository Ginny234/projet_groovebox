#ifndef STRUCT_H
#define STRUCT_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Bounce.h>

#define NBR_SEQUENCES 4
#define NBR_BOUTONS 7
#define NBR_BOUTONS_SON 7

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   13  // Teensy 4 ignores this, uses pin 13


#define PIN_BOUTON_REC 10


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MARGE_HMIN 5

#define VOLUME_MIN 0.0f
#define VOLUME_MAX 1.0f
#define VOLUME_STEP 0.05f

#define OLED_RESET -1

#define CLK 34
#define DT 33
#define SW 35

typedef enum {
  AUCUN,
  REVERB,
  ROBOTIQUE,
}effet;

typedef enum {
  MENU,
  NORMAL,
  ENREGISTREMENT_SEQUENCE,
  LECTURE_SEQUENCE,
}etat;

typedef struct sequence sequence;
struct sequence{
  int id_sample;
  sequence* suiv;
};

#endif