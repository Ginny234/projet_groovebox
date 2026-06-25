# Projet Groovebox 2026

--------------------------------------------------
## Membres du groupe et rôles:

Richeter Marie  - FL, UX / intégration 
Audran Elodie   - FL, Cheffe de projet 
Boittin Mathias - FL, Lead mécanique / CAO 
Gharbi Irame    - Lead Software / DSP 
Zairi Rayen     - Lead électronique 	
--------------------------------------------------

## Description:

Une groovebox est un instrument de production musicale électronique autonome permettant de générer des sons après l'appuie de boutons physiques. Ces instrument proposent aussi généralement d'autres fonctionnalités telles qu'un séquenceur par exemple.

Notre objectif etait de créer une groovebox complète et fonctionnelle, jouant des samples stockés dans une carte SD. Les fonctionnalités finales de noutres groovebox sont celles si:
- Séquenceur, permet d'enrgistrer jusqu'à 4 séquences pouvant êtres jouées en même temps que des samples "libres"
- Gestion du volume et possibilité de rendre un son plus aigus ou grave via des potentiomètres
- Possibilité d'enregistrer un son avec le microphone pouvant être déclenché via le bouton d'enrgistrement et d'être modifier en appuyant plus de 3 secondes dessus

--------------------------------------------------
# Dépendances

- Teensy board manager
- Adafruit GFX librairy
- Adafuit SSD1306
--------------------------------------------------

## Instructions de compilation

- Mettre en place le board manager Teensy (de préference Teensy 4.1)
- Installer les bibliothèques Adafruit GFX library et Adafruit SSD1306
- Ouvrir le dossier main et le fichier du même nom sur arduino
- Cliquez sur upload pour transferer le code sur la Teensy

--------------------------------------------------

## Structure du code

/PROJET_GROOVEBOX
├── /hardware                   # Schéma électronique
├── /cao                        # Fichiers boitier
├── /main
│   ├── /src
│   │   ├── affichage.h         # Fonctions liés à l'affichage et l'écran
│   │   ├── affichage.cpp         
│   │   ├── menus.h             # Gestions des menus et naviguation dans états
│   │   ├── menus.cpp                
│   │   ├── modif_sons.h        # Modification des sons: effets, volume ...
│   │   ├── modif_sons.cpp                
│   │   ├── samples.h           # Gestion de la lecture des samples et des séquences
│   │   ├── samples.cpp              
│   │   ├── sequences.h         # Gestion des séquences (enregistrement, sauvegarde sur carte SD...)
│   │   ├── sequences.cpp              
│   │   ├── var_global.h        # Toutes variables globales du programme: système audio, boutons....
│   │   ├── var_global.cpp              
│   │   └── struct.h            # Définition des structure etc
│   └── main.ino          
└── README.md

