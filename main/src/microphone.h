#ifndef MICROPHONE_H
#define MICROPHONE_H

void microphoneSetup();
void microphoneLoop();
void handleButton();
void startRecording();
void continueRecording();
void stopRecording();
void playRecording();
extern bool recording;
extern bool playing;

#endif