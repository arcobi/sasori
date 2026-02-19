#include "imu.h"
#include <Wire.h>

void IMU::setup() {
    Wire.begin(IMU_SDA, IMU_SCL);
    mpu.setup(IMU_ADDRESS);
    delay(1000);
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();
}

void IMU::update() {
    if (mpu.update()) {
        yaw = mpu.getYaw();
    }
}

float IMU::getYaw() {
    return yaw;
}
