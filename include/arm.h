#ifndef ARM_H
#define ARM_H

#include <ESP32Servo.h>

#define GRIPPER_PIN 15
#define GRIPPER_CLOSED 60
#define GRIPPER_OPEN 180

class Arm {
    public:
        void setup();
        void pause();
        void unpause();
        void update();

        void goTo(const float z, const float phi, const float r);
        void relativeMove(const float z, const float phi, const float r);
        bool hasArrived();

        void grip();
        void release();

    private:
        volatile int posPrimary;
        volatile int posSecondary;
        volatile int posTurret;

        volatile int targetPosPrimary;
        volatile int targetPosSecondary;
        volatile int targetPosTurret;

        volatile float targetRho;
        volatile float targetPhi;
        volatile float targetR;

        float currentArmSpeed;
        unsigned long lastPoll;

        Servo gripper;
        bool gripping;
};

extern Arm arm;

#endif
