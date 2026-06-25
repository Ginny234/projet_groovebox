#include "modifs_son.h"
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

void aigue_grave(){
  // =========================
// POTENTIOMÈTRE + LISSAGE
// =========================
long somme = 0;
for (int i = 0; i < 16; i++) {
  somme += analogRead(A7);
}

int valeurA7 = somme / 16;

static float smoothedKnob = 0.5f;
float knob = (float)valeurA7 / 1023.0f;

// inversion sens (gauche = grave, droite = aigu)
knob = 1.0f - knob;

smoothedKnob = 0.25f * knob + 0.75f * smoothedKnob;

// =========================
// PITCH STEPS
// =========================
const float pitchSteps[] = {0.35f, 0.55f, 0.80f, 1.20f, 1.80f, 2.80f};
const int pitchStepCount = sizeof(pitchSteps) / sizeof(pitchSteps[0]);
int pitchIndex = (int)(smoothedKnob * (pitchStepCount - 1) + 0.5f);
if (pitchIndex < 0) pitchIndex = 0;
if (pitchIndex >= pitchStepCount) pitchIndex = pitchStepCount - 1;
float pitchRatio = pitchSteps[pitchIndex];

// =========================
// SOLUTION 3 (ANTI SATURATION)
// =========================
if (pitchRatio < 0.6f) {
  pitchRatio = 0.6f;
}

if (pitchRatio > 1.6f) {
  pitchRatio = 1.6f;
}
pitch_courant = pitchRatio; // On l'enregistre pour l'afficher plus tard
pitch_brut_courant = valeurA7;

// =========================
// UPDATE AUDIO
// =========================
static float ancienPitch = -1.0f;
if (pitchRatio != ancienPitch) {
    granular1.setSpeed(pitchRatio);
    ancienPitch = pitchRatio;
  Serial.print("A7=");
  Serial.print(valeurA7);
  Serial.print(" Pitch=");
  Serial.println(pitchRatio, 2);
}
}