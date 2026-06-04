// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-3: Playing Samples

// WAV files converted to code by wav2sketch
#include "AudioSampleSnare.h"        // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"       // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"        // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleKick.h"         // http://www.freesound.org/people/DWSD/sounds/171104/
#include "AudioSampleGong.h"         // http://www.freesound.org/people/juskiddink/sounds/86773/
#include "AudioSampleCashregister.h" // http://www.freesound.org/people/kiddpark/sounds/201159/
#include <Bounce.h>


///////////////////////////////////
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlayMemory          playMem3;  //xy=220.33332061767578,352.333309173584
AudioPlayMemory          playMem2;       //xy=244.3333282470703,293.3333282470703
AudioPlayMemory          playMem4; //xy=246.33330535888672,411.3333387374878
AudioPlayMemory          playMem1;       //xy=257.3333282470703,207.3333282470703
AudioMixer4              mixer1;         //xy=471.3333282470703,217.3333282470703
AudioOutputI2S           i2s1;           //xy=671.3333282470703,240.3333282470703
AudioConnection          patchCord1(playMem3, 0, mixer1, 2);
AudioConnection          patchCord2(playMem2, 0, mixer1, 1);
AudioConnection          patchCord3(playMem4, 0, mixer1, 3);
AudioConnection          patchCord4(playMem1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=395.3333282470703,341.3333282470703
// GUItool: end automatically generated code

///////////////////////////////////





// Bounce objects to read pushbuttons 
Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);  // 15 ms debounce time
Bounce button2 = Bounce(2, 15);


void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  mixer1.gain(0, 0.4);
  mixer1.gain(1, 0.4);
  mixer1.gain(2, 0.4);
  mixer1.gain(3, 0.4);
  printf("a\n");
}

void loop() {
  // Update all the button objects
  button0.update();
  button1.update();
  button2.update();

  if (button0.fallingEdge()) {
    printf("bah aussi\n");
    playMem1.play(AudioSampleSnare);
  }
  if (button1.fallingEdge()) {
    playMem2.play(AudioSampleTomtom);
  }
  if (button2.fallingEdge()) {
    playMem3.play(AudioSampleHihat);
  }

/*
  int knob = analogRead(A3);
  if (button0.fallingEdge()) {
    if (knob < 512) {
      playMem1.play(AudioSampleSnare);
    } else {
      playMem1.play(AudioSampleKick);
    }
  }
  if (button1.fallingEdge()) {
    if (knob < 512) {
      playMem2.play(AudioSampleTomtom);
    } else {
      playMem4.play(AudioSampleGong);
    }
  }
  if (button2.fallingEdge()) {
    if (knob < 512) {
      playMem3.play(AudioSampleHihat);
    } else {
      playMem3.play(AudioSampleCashregister);
    }
  }
*/

}

