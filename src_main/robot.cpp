#include "robot.h"
#include "hal/can_data.h"
#include "hal/can_manager.h"
#include "Bcontroller.h"
#include <math.h>
#include <cstdint>

Robot::Robot() {
}

void Robot::setup() {
    arm.setup();
    imu.setup();
}

void Robot::update() {
    imu.update();
    this->updateSwerve();
    this->updateArm();
}

void Robot::updateArm() {
    arm.update();
}

void Robot::updateSwerve() {
    if (BC.commandSent == false) {
        SwerveUpdateData data;

        data.rx = static_cast<int16_t>(BC.LastRJoyStickX);
        data.ry = static_cast<int16_t>(BC.LastRJoyStickY);
        data.lx = static_cast<int16_t>(BC.LastLJoyStickX);
        data.ly = static_cast<int16_t>(BC.LastLJoyStickY);

        ESPcan.updateSwerve(data);
        BC.commandSent = true;
    }
}
