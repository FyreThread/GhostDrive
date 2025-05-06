#ifndef GHOSTDRIVE_HPP
#define GHOSTDRIVE_HPP

#include "pros/apix.h"
extern pros::Controller master;

// Change as needed
struct InputFrame {
  int timestamp;
  int axis3;
  int axis1;
  bool buttonA;
};

void startRecording();
void stopRecording();
void playRecording();
void resetGhostData();

extern InputFrame inputLog[1500];
extern int logIndex;

#endif
