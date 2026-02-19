#include <Arduino.h>
#include "robot.h"
#include "swerve.h"
#include "Bcontroller.h"
#include "hal/can_manager.h"
#include "arm.h"
#include "imu.h"

BluetoothController BC;
Robot perry;
CanCommunicator ESPcan;
Arm arm;
IMU imu;

void setup() {
    Serial.begin(115200);
    ESPcan.setup(500E3);
    BC.connect();
    perry.setup();
}

void loop() {
    perry.update();
}
