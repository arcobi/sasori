#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <MPU9250.h>

#define IMU_SDA 23
#define IMU_SCL 22
#define IMU_ADDRESS 0x68

class IMU {
    public:
        void setup();
        void update();
        float getYaw();

    private:
        MPU9250 mpu;
        float yaw;
};

extern IMU imu;

#endif
