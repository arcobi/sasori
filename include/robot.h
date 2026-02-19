#ifndef ROBOT_H
#define ROBOT_H

#include "arm.h"
#include "imu.h"
#include "hal/can_manager.h"
#include "Bcontroller.h"
#include <ESP32-TWAI-CAN.hpp>

class Robot {
    public:
        Robot();
        void setup();
        void update();
        void updateSwerve();
        void updateArm();
};

extern Robot perry;

#endif