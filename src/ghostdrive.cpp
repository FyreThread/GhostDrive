#include "ghostdrive.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <stdio.h>

InputFrame inputLog[1500];
int logIndex = 0;
int lastRecordTime = 0;

void saveRecordingToSD() {
  FILE *file = fopen("/usd/ghostlog.csv", "w");
  if (file == NULL) {
    pros::lcd::set_text(1, "SD write failed!");
    return;
  }

  for (int i = 0; i < logIndex; i++) {
    fprintf(file, "%d,%d,%d,%d\n", inputLog[i].timestamp, inputLog[i].axis3,
            inputLog[i].axis1, inputLog[i].buttonA ? 1 : 0);
  }

  fclose(file);
  pros::lcd::set_text(1, "Recording saved to SD.");
}

void startRecording() {
  logIndex = 0;
  lastRecordTime = pros::millis();

  while (/* condition to keep recording */) {
    int now = pros::millis();
    if (now - lastRecordTime >= 20 && logIndex < 1500) {
      inputLog[logIndex++] = {
          now,
          pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER,
                                         pros::E_CONTROLLER_ANALOG_LEFT_Y),
          pros::c::controller_get_analog(pros::E_CONTROLLER_MASTER,
                                         pros::E_CONTROLLER_ANALOG_RIGHT_X),
          static_cast<bool>(pros::c::controller_get_digital(
              pros::E_CONTROLLER_MASTER,
              pros::E_CONTROLLER_DIGITAL_A)) // returns bool
      };
      lastRecordTime = now;
    }
    pros::delay(5);
  }
  saveRecordingToSD();
}

void loadRecordingFromSD() {
  FILE *file = fopen("/usd/ghostlog.csv", "r");
  if (file == NULL) {
    pros::lcd::set_text(1, "SD read failed!");
    return;
  }

  logIndex = 0;
  while (fscanf(file, "%d,%d,%d,%d\n", &inputLog[logIndex].timestamp,
                &inputLog[logIndex].axis3, &inputLog[logIndex].axis1,
                (int *)&inputLog[logIndex].buttonA) == 4 &&
         logIndex < 1500) {
    logIndex++;
  }

  fclose(file);
  pros::lcd::set_text(1, "Recording loaded from SD.");
}

void playRecording() {
  int playbackStart = pros::millis();
  int currentIndex = 0;

  while (currentIndex < logIndex) {
    int elapsed = pros::millis() - playbackStart;

    if (elapsed >= inputLog[currentIndex].timestamp) {
      // Drive logic
      int left = inputLog[currentIndex].axis3;
      int right = inputLog[currentIndex].axis1;

      // Replace with your actual motor control
      pros::Motor leftMotor(1);
      pros::Motor rightMotor(2);
      leftMotor.move(left);
      rightMotor.move(right);

      currentIndex++;
    }

    pros::delay(2);
  }
}

void stopRecording() {
  // Implement a button press or external signal to break the loop
}

void resetGhostData() { logIndex = 0; }
