#include <Arduino.h>
#include "Bcontroller.h"
#include "drive.h"
#include "arm.h"

BluetoothController BC;
Robot perry;
Arm arm;

void setup() {
    Serial.begin(115200);
    BC.connect();
    perry.setup();
    arm.setup();
}

void loop() {
    perry.update();
    arm.update();
}
