GhostDrive: VEX V5 Controller Input Recorder & Replayer

GhostDrive is a PROS-based project for the VEX V5 Robotics platform that enables the recording and replaying of controller inputs during a match. The system allows for capturing joystick movements and button presses during driver control and playing them back automatically during autonomous mode, ensuring consistent and repeatable behaviors.


Features

    Record and Replay Inputs: Capture joystick and button presses in opcontrol() and replay them during autonomous().

    SD Card Persistence: Save recorded inputs to the VEX Brain's SD card, ensuring data is available across reboots and matches.

    Real-time Playback: Accurate, time-aligned input playback based on recorded timestamps.

    Simple Interface: Easy-to-use functions to start, stop, and load recordings.

Installation
Requirements:

    VEX V5 Brain with SD card installed

    PROS 3.1 or later

    Clone the Repository:

    git clone https://github.com/YourUsername/GhostDrive.git

    Open the Project in the PROS IDE.

    Upload the project to your VEX V5 Brain.

Usage

1. Recording Inputs

In opcontrol(), the system starts recording whenever you call startRecording(). The inputs are logged at a fixed interval.

void opcontrol() {
  startRecording();
  // Add your control code here
}

Once recording is complete, the data is automatically saved to the SD card as a .csv file.
2. Replaying Inputs

In autonomous(), you can load the saved input log and use playRecording() to simulate the recorded driver inputs.

void autonomous() {
  loadRecordingFromSD(); // Load recorded input data
  playRecording();      // Playback the inputs during autonomous
}

3. Stopping Recording

You can add a button (e.g., ButtonX) to stop the recording:

void opcontrol() {
  if (Controller1.ButtonX.pressing()) {
    stopRecording();
  }
}

File Structure

/src
  ├── ghostdrive.cpp     # Main logic for recording and replaying
  ├── ghostdrive.hpp     # Header file with function declarations
  └── main.cpp           # Entry point, handles opcontrol and autonomous

/include
  └── ghostdrive.hpp     # Declaration of functions and structs

/usd
  └── ghostlog.csv       # Recorded input log (saved to SD card)

Functions
startRecording()

Starts recording inputs from the controller, capturing joystick positions and button presses.
saveRecordingToSD()

Saves the recorded inputs to a file on the SD card (/usd/ghostlog.csv).
loadRecordingFromSD()

Loads the recorded inputs from the SD card and prepares them for playback.
playRecording()

Plays back the recorded inputs, controlling the robot's motors based on the logged data.

Example Usage
opcontrol.cpp

#include "ghostdrive.hpp"

void opcontrol() {
  startRecording(); // Start recording controller inputs

  // Your control code here...
  
  if (Controller1.ButtonX.pressing()) {
    stopRecording();  // Stop recording when ButtonX is pressed
  }
}

autonomous.cpp

#include "ghostdrive.hpp"

void autonomous() {
  loadRecordingFromSD(); // Load recorded input data from SD card
  playRecording();      // Replay inputs during autonomous
}

Customizing

    You can easily add more buttons or joystick axes to the InputFrame struct for more complex input logging.

    Change the recording interval or file name to match your team's needs.

    Implement a kill switch or any conditions you need to stop or modify the recording in real-time.

License

  This project is licensed under the MIT License - see the LICENSE file for details.

Contributions

  We welcome contributions! If you'd like to improve or extend this project, feel free to fork the repository and submit a pull request.

Acknowledgments

    PROS for the awesome VEX programming environment.

    VEX Robotics for the VEX V5 platform.
